#include "cryptophases.h"

// Key Generation Phase
void CryptoPhases::KeyGeneration() {
    try {
        AutoSeededRandomPool rng;

        // Generate a 256-bit symmetric key for AES
        SecByteBlock symKey(AES::DEFAULT_KEYLENGTH);
        rng.GenerateBlock(symKey, symKey.size());

        // Save the symmetric key to a file
        FileSink fileSymKey("sym_key.bin");
        fileSymKey.Put(symKey, symKey.size());

        // Generate a 2048-bit RSA key pair
        InvertibleRSAFunction rsaParams;
        rsaParams.Initialize(rng, 2048);

        RSA::PrivateKey privateKey(rsaParams);
        RSA::PublicKey publicKey(rsaParams);

        // Save the public and private keys to files
        publicKey.Save(FileSink("public.key").Ref());
        privateKey.Save(FileSink("private.key").Ref());

        std::cout << "Key generation successful!" << std::endl;
    }
    catch (const Exception& e) {
        std::cerr << "Crypto++ exception: " << e.what() << std::endl;
    }
}

// Encryption Phase
void CryptoPhases::EncryptFile(const std::string& inputFile, const std::string& outputFile) {
    try {
        AutoSeededRandomPool rng;

        // Load the symmetric key from the file
        SecByteBlock symKey(AES::DEFAULT_KEYLENGTH);
        FileSource fileSymKey("sym_key.bin", false);
        fileSymKey.Pump(AES::DEFAULT_KEYLENGTH);
        fileSymKey.Get(symKey, symKey.size());

        // Encrypt the image file using AES in CBC mode
        CBC_Mode<AES>::Encryption aesEncryptor;
        aesEncryptor.SetKeyWithIV(symKey, symKey.size(), symKey); // Using the key as IV (not recommended)

        FileSource(inputFile.c_str(), true,
            new StreamTransformationFilter(aesEncryptor,
                new FileSink(outputFile.c_str())
            )
        );

        // Load the RSA public key from the file
        RSA::PublicKey publicKey;
        publicKey.Load(FileSource("public.key", true).Ref());

        // Encrypt the symmetric key using the RSA public key
        std::string encryptedSymKey;
        RSAES_OAEP_SHA_Encryptor rsaEncryptor(publicKey);

        StringSource(symKey, symKey.size(), true,
            new PK_EncryptorFilter(rng, rsaEncryptor,
                new StringSink(encryptedSymKey)
            )
        );

        // Save the encrypted symmetric key to a file
        FileSink fileEncSymKey("sym_key.bin.enc");
        fileEncSymKey.Put((const byte*)encryptedSymKey.data(), encryptedSymKey.size());

        std::cout << "Encryption successful!" << std::endl;
    }
    catch (const Exception& e) {
        std::cerr << "Crypto++ exception: " << e.what() << std::endl;
    }
}

// Decryption Phase
void CryptoPhases::DecryptFile(const std::string& inputFile, const std::string& outputFile) {
    try {
        AutoSeededRandomPool rng;

        // Load the RSA private key from the file
        RSA::PrivateKey privateKey;
        privateKey.Load(FileSource("private.key", true).Ref());

        // Load the encrypted symmetric key from the file
        std::string encryptedSymKey;
        FileSource("sym_key.bin.enc", true, new StringSink(encryptedSymKey));

        // Decrypt the symmetric key using the RSA private key
        SecByteBlock symKey(AES::DEFAULT_KEYLENGTH);
        RSAES_OAEP_SHA_Decryptor rsaDecryptor(privateKey);

        StringSource(encryptedSymKey, true,
            new PK_DecryptorFilter(rng, rsaDecryptor,
                new ArraySink(symKey, symKey.size())
            )
        );

        // Decrypt the encrypted image file using AES in CBC mode
        CBC_Mode<AES>::Decryption aesDecryptor;
        aesDecryptor.SetKeyWithIV(symKey, symKey.size(), symKey); // Using the key as IV (not recommended)

        FileSource(inputFile.c_str(), true,
            new StreamTransformationFilter(aesDecryptor,
                new FileSink(outputFile.c_str())
            )
        );

        std::cout << "Decryption successful!" << std::endl;
    }
    catch (const Exception& e) {
        std::cerr << "Crypto++ exception: " << e.what() << std::endl;
    }
}
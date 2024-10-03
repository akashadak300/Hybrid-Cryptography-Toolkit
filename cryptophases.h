#ifndef CRYPTOPHASES_H
#define CRYPTOPHASES_H

#include <osrng.h>     // For AutoSeededRandomPool (random number generator)
#include <aes.h>       // For AES encryption
#include <modes.h>     // For CBC_Mode (Cipher Block Chaining mode)
#include <rsa.h>       // For RSA key generation
#include <files.h>     // For FileSink and FileSource (file handling)
#include <secblock.h>  // For SecByteBlock (secure byte storage)
#include <cryptlib.h>  // For Exception handling
#include <iostream>

using namespace CryptoPP;

class CryptoPhases {
public:
    void KeyGeneration();
    void EncryptFile(const std::string& inputFile, const std::string& outputFile);
    void DecryptFile(const std::string& inputFile, const std::string& outputFile);
};

#endif // CRYPTOPHASES_H
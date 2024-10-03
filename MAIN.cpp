#include "cryptophases.h"

int main() {
    CryptoPhases crypto;

    // Key Generation Phase
    crypto.KeyGeneration();

    // Encryption Phase
    crypto.EncryptFile("image.jpg", "image.jpg.enc");

    // Decryption Phase
    crypto.DecryptFile("image.jpg.enc", "DEC_image.jpg");

    return 0;
}
# Hybrid Cryptography Toolkit Using Crypto++

## Project Overview
The **Hybrid Cryptography Toolkit** is designed to securely encrypt and decrypt large files by combining the strengths of symmetric (AES) and asymmetric (RSA) encryption algorithms. This project utilizes the **Crypto++ library** to perform the encryption and decryption operations.

### Objectives:
- Encrypt large files (e.g., images) using AES for fast encryption of data.
- Secure the AES key using RSA encryption.
- Decrypt the files using the RSA private key to retrieve the AES key, followed by AES decryption of the file.

## Features
1. **Symmetric Encryption (AES)**: Encrypt files with AES (128, 192, or 256-bit key).
2. **Asymmetric Encryption (RSA)**: Encrypt the AES key using RSA (2048-bit key pair).
3. **File Handling**: Encryption and decryption of large files (e.g., images) with secure storage of keys.
4. **Crypto++ Library Integration**: Implementation of cryptographic algorithms using Crypto++.

## Project Phases

### 1. Setup Phase
   - **Objective**: Set up environment and link Crypto++ libraries.
   - **Tasks**:
     - Include necessary headers.
     - Link Crypto++ libraries to handle encryption and decryption.

### 2. Key Generation Phase
   - **Symmetric Key**: Generates a 64/128/256-bit symmetric AES key.
   - **Asymmetric Key**: Generates a 2048-bit RSA public/private key pair.
   - **File Outputs**:
     - `sym_key.bin` - Stores the AES key.
     - `public.key` - Stores the RSA public key.
     - `private.key` - Stores the RSA private key.

### 3. Encryption Phase
   - **AES Encryption**: Encrypts the file (e.g., `image.jpg`) with the AES key.
     - Output: `image.jpg.enc`
   - **RSA Encryption**: Encrypts the AES key with RSA public key.
     - Output: `sym_key.bin.enc`

### 4. Decryption Phase
   - **RSA Decryption**: Decrypts the AES key using the RSA private key.
     - Output: `sym_key.bin`
   - **AES Decryption**: Decrypts the encrypted file using the decrypted AES key.
     - Output: Original image file.

## Cryptographic Algorithms Used
- **AES (Advanced Encryption Standard)**: Used for fast and efficient file encryption.
  - Supports key sizes: 128, 192, 256 bits.
  - Operates on 128-bit blocks of data.
- **RSA (Rivest-Shamir-Adleman)**: Used for secure key transmission.
  - 2048-bit key size for encryption of AES key.

## Tools & Technologies
- **Crypto++ Library**: A C++ class library used for cryptographic algorithms and protocols.
- **C++**: Core programming language used to implement the encryption and decryption phases.
  
## How to Run
1. **Setup**: Install Crypto++ and link it to your project.
2. **Compile**: Compile the project using a C++ compiler with Crypto++ support.
3. **Execute**: Run the executable to perform key generation, encryption, and decryption.

## Future Enhancements
- Add support for additional encryption algorithms (e.g., DES, RC4).
- Implement a graphical user interface (GUI) for easier file encryption and decryption.
- Explore adding integrity checks (e.g., SHA-256 hashing) to ensure file authenticity.

## License
This project is open-source and available under the [MIT License](LICENSE).

#include <string.h>
#include <stdio.h>
#include "security.h"
#include <openssl/sha.h>  // External library for hashing

void hashPassword(const char* password, char* hashedPassword) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password, strlen(password), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashedPassword + (i * 2), "%02x", hash[i]);
    }
}

int verifyPassword(const char* inputPassword, const char* storedHashedPassword) {
    char hashedInput[65];  // SHA256 produces 64 characters
    hashPassword(inputPassword, hashedInput);
    return strcmp(hashedInput, storedHashedPassword) == 0;
}

// A simple XOR-based encryption
void encryptData(char* data, const char* key) {
    for (int i = 0; i < strlen(data); i++) {
        data[i] ^= key[i % strlen(key)];
    }
}

// Decryption uses the same logic as encryption
void decryptData(char* data, const char* key) {
    encryptData(data, key);  // XORing twice with the same key decrypts the data
}


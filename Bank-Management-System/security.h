#ifndef SECURITY_H
#define SECURITY_H

void hashPassword(const char* password, char* hashedPassword);
int verifyPassword(const char* inputPassword, const char* storedHashedPassword);
void encryptData(char* data, const char* key);
void decryptData(char* data, const char* key);

#endif // SECURITY_H


#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

class CaesarCipher {
public:
    CaesarCipher();
    char* Encrypt(const char* text, int key);
    char* Decrypt(const char* text, int key);
};

#endif

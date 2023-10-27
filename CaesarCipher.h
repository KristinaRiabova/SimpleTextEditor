#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

class CaesarCipher {
public:
    CaesarCipher();
    ~CaesarCipher();

    char* Encrypt(const char* text, int key);
    char* Decrypt(const char* text, int key);

private:
    static void* handle;
};

#endif

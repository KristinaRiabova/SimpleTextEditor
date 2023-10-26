#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

class CaesarCipher {
public:
    CaesarCipher();
    ~CaesarCipher(); // Explicit destructor declaration

    char* Encrypt(const char* text, int key);
    char* Decrypt(const char* text, int key);

private:
    static void* handle; // Private static member variable
};

#endif

#include <dlfcn.h>
#include "CaesarCipher.h"


void* CaesarCipher::handle = nullptr;

CaesarCipher::CaesarCipher() {

    handle = dlopen("/Users/kristina_mbp/CLionProjects/CaesarEncryptionAlgorithm/caesar.dylib", RTLD_LAZY);
    if (!handle) {
        handle = nullptr;
    }
}

CaesarCipher::~CaesarCipher() {

    if (handle) {
        dlclose(handle);
    }
}

char* CaesarCipher::Encrypt(const char* text, int key) {
    if (!handle) {
        return nullptr;
    }

    char* (*encryptFunction)(const char*, int) = (char* (*)(const char*, int))dlsym(handle, "encrypt");
    if (!encryptFunction) {
        return nullptr;
    }

    char* encryptedText = encryptFunction(text, key);
    return encryptedText;
}

char* CaesarCipher::Decrypt(const char* text, int key) {
    if (!handle) {
        return nullptr;
    }

    char* (*decryptFunction)(const char*, int) = (char* (*)(const char*, int))dlsym(handle, "decrypt");
    if (!decryptFunction) {
        return nullptr;
    }

    char* decryptedText = decryptFunction(text, key);
    return decryptedText;
}

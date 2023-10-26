#include "CaesarCipher.h"
#include <dlfcn.h>

CaesarCipher::CaesarCipher() {}

char* CaesarCipher::Encrypt(const char* text, int key) {
    void* handle = dlopen("/Users/kristina_mbp/CLionProjects/CaesarEncryptionAlgorithm/caesar.dylib", RTLD_LAZY);
    if (!handle) {

        return nullptr;
    }

    char* (*encryptFunction)(const char*, int) = (char* (*)(const char*, int))dlsym(handle, "encrypt");
    if (!encryptFunction) {

        dlclose(handle);
        return nullptr;
    }

    char* encryptedText = encryptFunction(text, key);
    dlclose(handle);
    return encryptedText;
}

char* CaesarCipher::Decrypt(const char* text, int key) {
    void* handle = dlopen("/Users/kristina_mbp/CLionProjects/CaesarEncryptionAlgorithm/caesar.dylib", RTLD_LAZY);
    if (!handle) {

        return nullptr;
    }

    char* (*decryptFunction)(const char*, int) = (char* (*)(const char*, int))dlsym(handle, "decrypt");
    if (!decryptFunction) {

        dlclose(handle);
        return nullptr;
    }

    char* decryptedText = decryptFunction(text, key);
    dlclose(handle);
    return decryptedText;
}

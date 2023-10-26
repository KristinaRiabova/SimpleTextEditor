#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "CaesarCipher.h"

class CommandProcessor {
public:
    CommandProcessor();
    char* ProcessEncrypt(const char* text, int key);
    char* ProcessDecrypt(const char* text, int key);

private:
    CaesarCipher cipher;
};

#endif

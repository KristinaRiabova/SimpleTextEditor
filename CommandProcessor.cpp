#include "CommandProcessor.h"

CommandProcessor::CommandProcessor() {}

char* CommandProcessor::ProcessEncrypt(const char* text, int key) {
    return cipher.Encrypt(text, key);
}

char* CommandProcessor::ProcessDecrypt(const char* text, int key) {
    return cipher.Decrypt(text, key);
}

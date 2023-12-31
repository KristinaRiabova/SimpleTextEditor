#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H
#include "CaesarCipher.h"
#include "TextStorage.h"

class CommandProcessor {
public:
    CommandProcessor(TextStorage& storage, CaesarCipher& cipher);

    void ProcessUserChoice(int choice);
    void AppendText(const std::string& textToAdd);
    void StartNewLine();
    void Undo();
    void Redo();
    void Cut(size_t lineIndex, size_t index, size_t length);
    void Copy(size_t lineIndex, size_t index, size_t length);
    void Paste(size_t lineIndex, size_t index);
    void InsertWithReplacement(size_t lineIndex, size_t index, const std::string& text);
    void Delete(size_t lineIndex, size_t index, size_t length);
    void PrintText();
    void SearchForText(const std::string& substring);
    void LoadTextFromFile(const std::string& filename);
    void SaveTextToFile(const std::string& filename);
    void InsertSubstring(size_t lineIndex, size_t index, const std::string& substring);
    void EncryptText(int key);
    void DecryptText(int key);

private:
    TextStorage& storage;
    CaesarCipher& cipher;
};

#endif
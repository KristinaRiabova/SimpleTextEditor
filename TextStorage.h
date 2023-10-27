#ifndef TEXTSTORAGE_H
#define TEXTSTORAGE_H

#include <string>
#include <vector>
#include <iostream>

#include "Line.h"

class TextStorage {
public:
    void AppendText(const std::string& text);
    void StartNewLine();
    void Undo();
    void Redo();
    void Cut(size_t lineIndex, size_t index, size_t length);
    void Copy(size_t lineIndex, size_t index, size_t length);
    void Paste(size_t lineIndex, size_t index);
    void InsertWithReplacement(size_t lineIndex, size_t index, const std::string& text);
    void Delete(size_t lineIndex, size_t index, size_t length);
    void PrintText();
    size_t SearchForText(const std::string& substring);
    void LoadTextFromFile(const std::string& filename);
    void SaveTextToFile(const std::string& filename);
    void InsertSubstring(size_t lineIndex, size_t index, const std::string& substring);
    std::string GetText();
    void SetText(const std::string& newText);

private:
    std::vector<Line> lines;
    std::vector<std::vector<Line>> history;
    size_t historyIndex = 0;
    std::string clipboard;
};

#endif

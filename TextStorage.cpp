#include "TextStorage.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>


void TextStorage::AppendText(const std::string& text) {
    if (!lines.empty()) {
        lines.back().Append(text);
    } else {
        lines.emplace_back(text);
    }
    history.push_back(lines);
}

void TextStorage::StartNewLine() {
    lines.emplace_back("");
    history.push_back(lines);
}

void TextStorage::Undo() {
    if (historyIndex > 0) {
        historyIndex--;
        lines = history[historyIndex];
    }
}

void TextStorage::Redo() {
    if (historyIndex < history.size() - 1) {
        historyIndex++;
        lines = history[historyIndex];
    }
}

void TextStorage::Cut(size_t lineIndex, size_t index, size_t length) {
    if (lineIndex < lines.size()) {
        std::string cutText = lines[lineIndex].GetText().substr(index, length);
        clipboard = cutText;
        lines[lineIndex].Delete(index, length);
        history.push_back(lines);
        historyIndex = history.size() - 1;
    }
}

void TextStorage::Copy(size_t lineIndex, size_t index, size_t length) {
    if (lineIndex < lines.size()) {
        clipboard = lines[lineIndex].GetText().substr(index, length);
    }
}

void TextStorage::Paste(size_t lineIndex, size_t index) {
    if (!clipboard.empty() && lineIndex < lines.size()) {
        lines[lineIndex].Insert(index, clipboard);
        history.push_back(lines);
        historyIndex = history.size() - 1;
    }
}

void TextStorage::InsertWithReplacement(size_t lineIndex, size_t index, const std::string& text) {
    if (lineIndex < lines.size() && index <= lines[lineIndex].GetText().length()) {
        std::string lineText = lines[lineIndex].GetText();
        const size_t replaceLength = std::min(text.length(), lineText.length() - index);

        if (replaceLength > 0) {
            lineText.replace(index, replaceLength, text.substr(0, replaceLength));
        } else {
            lineText.insert(index, text);
        }

        lines[lineIndex] = lineText;
        history.push_back(lines);
        historyIndex = history.size() - 1;
    }
}

void TextStorage::Delete(size_t lineIndex, size_t index, size_t length) {
    if (lineIndex < lines.size()) {
        lines[lineIndex].Delete(index, length);
        history.push_back(lines);
        historyIndex = history.size() - 1;
    }
}

void TextStorage::PrintText() {
    for (const auto& line : lines) {
        std::cout << line.GetText() << std::endl;
    }
}

size_t TextStorage::SearchForText(const std::string& substring) {
    bool found = false;
    for (size_t i = 0; i < lines.size(); ++i) {
        std::string lineText = lines[i].GetText();
        size_t pos = 0;
        while ((pos = lineText.find(substring, pos)) != std::string::npos) {
            std::cout << "Text is present in this position: " << i << " " << pos - 1 << std::endl;
            pos += substring.length();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Text not found." << std::endl;
    }
    return 0;
}

void TextStorage::LoadTextFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        lines.clear();
        std::string line;
        while (std::getline(file, line)) {
            lines.emplace_back(line);
        }
        file.close();
        history.clear();
        history.push_back(lines);
        historyIndex = 0;
        std::cout << "Text loaded from file: " << filename << std::endl;
    } else {
        std::cout << "Error opening file: " << filename << std::endl;
    }
}

void TextStorage::SaveTextToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& line : lines) {
            file << line.GetText() << std::endl;
        }
        file.close();
        std::cout << "Text saved to file: " << filename << std::endl;
    } else {
        std::cout << "Error opening file for saving: " << filename << std::endl;
    }
}

void TextStorage::InsertSubstring(size_t lineIndex, size_t index, const std::string& substring) {
    if (lineIndex < lines.size()) {
        lines[lineIndex].Insert(index, substring);
        history.push_back(lines);
        historyIndex = history.size() - 1;
    }
}

std::string TextStorage::GetText() {
    std::string text;
    for (const auto& line : lines) {
        text += line.GetText() + '\n';
    }
    return text;
}

void TextStorage::SetText(const std::string& newText) {
    lines.clear();
    std::istringstream iss(newText);
    std::string line;
    while (std::getline(iss, line)) {
        lines.emplace_back(line);
    }
    history.clear();
    history.push_back(lines);
    historyIndex = 0;
}


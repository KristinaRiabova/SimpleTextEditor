#include "CommandProcessor.h"
#include <iostream>
#include <string>

CommandProcessor::CommandProcessor(TextStorage& storage, CaesarCipher& cipher) : storage(storage), cipher(cipher) {}

void CommandProcessor::ProcessUserChoice(int choice) {
    switch (choice) {
        case 1: {
            std::string textToAdd;
            std::cout << "Enter text to append: ";
            std::cin.ignore();
            std::getline(std::cin, textToAdd);
            AppendText(textToAdd);
            break;
        }
        case 2: {
            StartNewLine();
            break;
        }
        case 3: {
            Undo();
            break;
        }
        case 4: {
            Redo();
            break;
        }
        case 5: {
            size_t lineIndex, index, length;
            std::cout << "Enter line index, start index, and length: ";
            std::cin >> lineIndex >> index >> length;
            Cut(lineIndex, index, length);
            break;
        }
        case 6: {
            size_t lineIndex, index, length;
            std::cout << "Enter line index, start index, and length: ";
            std::cin >> lineIndex >> index >> length;
            Copy(lineIndex, index, length);
            break;
        }
        case 7: {
            size_t lineIndex, index;
            std::cout << "Enter line index and start index: ";
            std::cin >> lineIndex >> index;
            Paste(lineIndex, index);
            break;
        }
        case 8: {
            size_t lineIndex, index;
            std::string text;
            std::cout << "Enter line index, start index, and text to insert: ";
            std::cin >> lineIndex >> index;
            std::cin.ignore();
            std::getline(std::cin, text);
            InsertWithReplacement(lineIndex, index, text);
            break;
        }
        case 9: {
            size_t lineIndex, index, length;
            std::cout << "Enter line index, start index, and length to delete: ";
            std::cin >> lineIndex >> index >> length;
            Delete(lineIndex, index, length);
            break;
        }
        case 10: {
            PrintText();
            break;
        }
        case 11: {
            std::string substring;
            std::cout << "Enter substring to search for: ";
            std::cin.ignore();
            std::getline(std::cin, substring);
            SearchForText(substring);
            break;
        }
        case 12: {
            std::string filename;
            std::cout << "Enter the filename to load text from: ";
            std::cin.ignore();
            std::getline(std::cin, filename);
            LoadTextFromFile(filename);
            break;
        }
        case 13: {
            std::string filename;
            std::cout << "Enter the filename to save text to: ";
            std::cin.ignore();
            std::getline(std::cin, filename);
            SaveTextToFile(filename);
            break;
        }
        case 14: {
            size_t lineIndex, index;
            std::string substring;
            std::cout << "Enter line index, start index, and substring to insert: ";
            std::cin >> lineIndex >> index;
            std::cin.ignore();
            std::getline(std::cin, substring);
            InsertSubstring(lineIndex, index, substring);
            break;
        }
        case 15: {
            int key;
            std::cout << "Enter the encryption key: ";
            std::cin >> key;
            EncryptText(key);
            break;
        }
        case 16: {
            int key;
            std::cout << "Enter the decryption key: ";
            std::cin >> key;
            DecryptText(key);
            break;
        }
        case 0: {
            std::cout << "Exiting the program." << std::endl;
            break;
        }
        default: {
            std::cout << "Invalid choice." << std::endl;
        }
    }
}

void CommandProcessor::AppendText(const std::string& textToAdd) {
    storage.AppendText(textToAdd);
}

void CommandProcessor::StartNewLine() {
    storage.StartNewLine();
}

void CommandProcessor::Undo() {
    storage.Undo();
}

void CommandProcessor::Redo() {
    storage.Redo();
}

void CommandProcessor::Cut(size_t lineIndex, size_t index, size_t length) {
    storage.Cut(lineIndex, index, length);
}

void CommandProcessor::Copy(size_t lineIndex, size_t index, size_t length) {
    storage.Copy(lineIndex, index, length);
}

void CommandProcessor::Paste(size_t lineIndex, size_t index) {
    storage.Paste(lineIndex, index);
}

void CommandProcessor::InsertWithReplacement(size_t lineIndex, size_t index, const std::string& text) {
    storage.InsertWithReplacement(lineIndex, index, text);
}

void CommandProcessor::Delete(size_t lineIndex, size_t index, size_t length) {
    storage.Delete(lineIndex, index, length);
}

void CommandProcessor::PrintText() {
    storage.PrintText();
}

void CommandProcessor::SearchForText(const std::string& substring) {
    storage.SearchForText(substring);
}

void CommandProcessor::LoadTextFromFile(const std::string& filename) {
    storage.LoadTextFromFile(filename);
}

void CommandProcessor::SaveTextToFile(const std::string& filename) {
    storage.SaveTextToFile(filename);
}

void CommandProcessor::InsertSubstring(size_t lineIndex, size_t index, const std::string& substring) {
    storage.InsertSubstring(lineIndex, index, substring);
}

void CommandProcessor::EncryptText(int key) {
    std::string currentText = storage.GetText();
    char* encryptedText = cipher.Encrypt(currentText.c_str(), key);
    if (encryptedText) {
        storage.SetText(encryptedText);
        delete[] encryptedText;
    } else {
        std::cout << "Error encrypting text." << std::endl;
    }
}

void CommandProcessor::DecryptText(int key) {
    std::string currentText = storage.GetText();
    char* decryptedText = cipher.Decrypt(currentText.c_str(), key);
    if (decryptedText) {
        storage.SetText(decryptedText);
        delete[] decryptedText;
    } else {
        std::cout << "Error decrypting text." << std::endl;
    }
}
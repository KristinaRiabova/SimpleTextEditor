#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Line {
public:
    Line(const std::string& text) : text(text) {}

    void Append(const std::string& textToAdd) {
        text += textToAdd;
    }

    void Insert(size_t index, const std::string& textToInsert) {
        text.insert(index, textToInsert);
    }

    void Delete(size_t index, size_t length) {
        text.erase(index, length);
    }

    std::string GetText() const {
        return text;
    }

private:
    std::string text;
};

class TextStorage {
public:
    void AppendText(const std::string& text) {
        if (!lines.empty()) {
            lines.back().Append(text);
        }
        else {
            lines.emplace_back(text);
        }
        history.push_back(lines);
    }

    void StartNewLine() {
        lines.emplace_back("");
        history.push_back(lines);
    }

    void Undo() {
        if (historyIndex > 0) {
            historyIndex--;
            lines = history[historyIndex];
        }
    }

    void Redo() {
        if (historyIndex < history.size() - 1) {
            historyIndex++;
            lines = history[historyIndex];
        }
    }

    void Cut(size_t lineIndex, size_t index, size_t length) {
        if (lineIndex < lines.size()) {
            std::string cutText = lines[lineIndex].GetText().substr(index, length);
            clipboard = cutText;
            lines[lineIndex].Delete(index, length);
            history.push_back(lines);
            historyIndex = history.size() - 1;
        }
    }

    void Copy(size_t lineIndex, size_t index, size_t length) {
        if (lineIndex < lines.size()) {
            clipboard = lines[lineIndex].GetText().substr(index, length);
        }
    }

    void Paste(size_t lineIndex, size_t index) {
        if (!clipboard.empty() && lineIndex < lines.size()) {
            lines[lineIndex].Insert(index, clipboard);
            history.push_back(lines);
            historyIndex = history.size() - 1;
        }
    }

    void InsertWithReplacement(size_t lineIndex, size_t index, const std::string& text) {
        if (lineIndex < lines.size()) {
            lines[lineIndex].Delete(index, text.length());
            lines[lineIndex].Insert(index, text);
            history.push_back(lines);
            historyIndex = history.size() - 1;
        }
    }

    void Delete(size_t lineIndex, size_t index, size_t length) {
        if (lineIndex < lines.size()) {
            lines[lineIndex].Delete(index, length);
            history.push_back(lines);
            historyIndex = history.size() - 1;
        }
    }

    void PrintText() {
        for (const auto& line : lines) {
            std::cout << line.GetText() << std::endl;
        }
    }
    size_t SearchForText(const std::string& substring) {
        size_t count = 0;
        for (size_t i = 0; i < lines.size(); ++i) {
            std::string lineText = lines[i].GetText();
            size_t pos = 0;
            while ((pos = lineText.find(substring, pos)) != std::string::npos) {
                std::cout << "Found at line " << i << ", index " << pos << std::endl;
                pos += substring.length();
                count++;
            }
        }
        return count;
    }
    void InsertSubstring(size_t lineIndex, size_t index, const std::string& substring) {
        if (lineIndex < lines.size()) {
            lines[lineIndex].Insert(index, substring);
            history.push_back(lines);
            historyIndex = history.size() - 1;
        }
    }

private:
    std::vector<Line> lines;
    std::vector<std::vector<Line>> history;
    size_t historyIndex = 0;
    std::string clipboard;
};

int main() {
    TextStorage storage;
    int choice;

    do {
        std::cout << "Choose the command:" << std::endl;
        std::cout << "1. Append text symbols to the end" << std::endl;
        std::cout << "2. Start a new line" << std::endl;
        std::cout << "3. Undo" << std::endl;
        std::cout << "4. Redo" << std::endl;
        std::cout << "5. Cut" << std::endl;
        std::cout << "6. Copy" << std::endl;
        std::cout << "7. Paste" << std::endl;
        std::cout << "8. Insert with replacement" << std::endl;
        std::cout << "9. Delete" << std::endl;
        std::cout << "10. Print the current text to console" << std::endl;
        std::cout << "11. Search for text" << std::endl;
        std::cout << "12. Load text from file" << std::endl;
        std::cout << "13. Save text to file" << std::endl;
        std::cout << "14. Insert substring" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::cout << "Enter text to append: ";
                std::string input;
                std::getline(std::cin, input);
                storage.AppendText(input);
                break;
            }
            case 2: {
                storage.StartNewLine();
                std::cout << "New line is started." << std::endl;
                break;
            }
            case 3: {
                storage.Undo();
                break;
            }
            case 4: {
                storage.Redo();
                break;
            }
            case 5: {
                std::cout << "Enter line, index, and number of symbols to cut: ";
                size_t lineIndex, index, length;
                std::cin >> lineIndex >> index >> length;
                storage.Cut(lineIndex, index, length);
                break;
            }
            case 6: {
                std::cout << "Enter line, index, and number of symbols to copy: ";
                size_t lineIndex, index, length;
                std::cin >> lineIndex >> index >> length;
                storage.Copy(lineIndex, index, length);
                break;
            }
            case 7: {
                std::cout << "Enter line and index to paste: ";
                size_t lineIndex, index;
                std::cin >> lineIndex >> index;
                storage.Paste(lineIndex, index);
                break;
            }
            case 8: {
                std::cout << "Enter line and index: ";
                size_t lineIndex, index;
                std::cin >> lineIndex >> index;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Write text: ";
                std::string text;
                std::getline(std::cin, text);
                storage.InsertWithReplacement(lineIndex, index, text);
                break;
            }
            case 9: {
                std::cout << "Enter line, index, and number of symbols to delete: ";
                size_t lineIndex, index, length;
                std::cin >> lineIndex >> index >> length;
                storage.Delete(lineIndex, index, length);
                break;
            }
            case 10: {
                std::cout << "Current Text:" << std::endl;
                storage.PrintText();
                break;
            }
            case 11: {
                std::cout << "Enter substring to search for: ";
                std::string substring;
                std::cin.ignore();
                std::getline(std::cin, substring);
                size_t count = storage.SearchForText(substring);
                std::cout << "Found " << count << " occurrences of '" << substring << "'" << std::endl;
                break;
            }
            case 14: {
                std::cout << "Enter line, index, and substring to insert: ";
                size_t lineIndex, index;
                std::string substring;
                std::cin >> lineIndex >> index;
                std::cin.ignore();
                std::getline(std::cin, substring);
                storage.InsertSubstring(lineIndex, index, substring);
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
    } while (choice != 0);

    return 0;
}
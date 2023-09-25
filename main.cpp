#include <iostream>
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

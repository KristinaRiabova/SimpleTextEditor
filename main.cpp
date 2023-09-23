#include <iostream>
#include <algorithm>

class Line {
public:
    Line(const std::string& text) : text(text) {}

    void Append(const std::string& textToAdd) {
        text += textToAdd;
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

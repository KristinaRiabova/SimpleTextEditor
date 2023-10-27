#include <iostream>
#include "CommandProcessor.h"
#include "TextStorage.h"

int main() {
    TextStorage storage;
    CaesarCipher cipher;
    CommandProcessor commandProcessor(storage, cipher);
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
        std::cout << "15. Encrypt text" << std::endl;
        std::cout << "16. Decrypt text" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        commandProcessor.ProcessUserChoice(choice);

    } while (choice != 0);

    return 0;
}

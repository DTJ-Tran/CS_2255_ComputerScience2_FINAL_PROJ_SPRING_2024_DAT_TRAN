#include "Menu.h"

Menu::Menu(const std::string& inputTitle, const std::vector<std::string>& inputOption) {
    setTitle(inputTitle);
    setOption(inputOption);
};  

Menu::Menu() {
    setTitle("");
    setOption(std::vector<std::string>()); // empty
};

std::string Menu::getTitle() const {
    return title; 
};

void Menu::setTitle(const std::string& inputTitle) {
    title = inputTitle;
    return;
};

std::vector<std::string> Menu::getOption() const {
    return option;
}; 

void Menu::setOption(const std::vector<std::string>& inputOption) {
    option = inputOption;
    return;
};

void Menu::displayMenu(int inputChoice) {
    std::string titleMessage = getTitle();
    std::string instructionMessage = "Use arrow keys to navigate, press Enter to select, Esc to exit.";
    std::vector<std::string> optionList = getOption();
    
    #ifdef _WIN32
        system("cls"); // Clear screen for Windows
        std::cout << titleMessage << std::endl;
    #else
        initscr(); // Initialize ncurses mode
        clear(); // Clear the screen in macOS (using ncurses)
        
    #endif

    // Print the title message
    #if __APPLE__
        int paddingLength = std::max(0, static_cast<int>(titleMessage.length()) - static_cast<int>(instructionMessage.length()));
        std::string padding(paddingLength, ' ');
        printw("%s%s\n", padding.c_str(), titleMessage.c_str());
    #endif

    // Print the menu options
    for (int i = 0; i < optionList.size(); i++) {
        
        if (inputChoice == i) {
            #ifdef _WIN32
                 std::cout << " > " << optionList[i] << std::endl;
            #else
                    printw("> %s\n", optionList[i].c_str());
            #endif
        } else {
            #ifdef _WIN32
                    std::cout << " " << optionList[i] << std::endl;
            #else
                    printw("  %s\n", optionList[i].c_str());
            #endif
        }
    }

   
    #ifdef __APPLE__
    // On macOS/Linux, refresh the screen after printing with ncurses
    refresh();
    printw("%s%s\n", padding.c_str(), instructionMessage.c_str());
    #endif

    return;
};

void Menu::runMenu() {

    int keyBoardInput = 0;
    int choice = 0; 
    int sizeMenu = option.size();
    displayMenu(choice);
    #ifdef _WIN32
         do{
            switch (keyBoardInput = _getch()) // Get a character from console without echoing it
            {
            case 72: // Up arrow
                choice = (choice - 1 + sizeMenu) % sizeMenu;
                break;
            case 80: // Down arrow
                choice = (choice + 1) % sizeMenu;
                break;
            case 13: // Enter
                handleChoice(choice);
                std::cout << std::endl;
                std::cout << "Press any key to continue...";
                _getch();
                break;
            case 27: // Escape
                std::cout << "Exiting...\n";
                return; // Exit the run() function
                break;
            default:
                std::cout << "Repress again\n";
                break;
            }
            displayMenu(choice); // do the re-update after repress
         } while (true);
    #else // for mac
        cbreak(); // Line buffering disabled
        //noecho(); // Turn off echoing of characters
        keypad(stdscr, TRUE); // Enable keypad mode for special keys
        do {
            keyBoardInput = getch();
            switch (keyBoardInput) {
                case KEY_UP: // Up arrow
                    choice = (choice - 1 + sizeMenu) % sizeMenu; // change choice to fit 
                    break;
                case KEY_DOWN: // Down arrow
                    choice = (choice + 1) % sizeMenu;      
                    break;
                case '\n': // Enter
                    handleChoice(choice);
                    printw("\n");
                    printw("Press any key to continue...");
                    getch();
                    break;
                case 27: // Escape
                    endwin(); // End ncurses mode before exiting
                    return; // Exit the program
                default:
                    printw("> %s\n", "Repress again\n");
                    getch();
                    break;
            }
            displayMenu(choice);
        } while (true);
        // End ncurses mode before exiting
        endwin();
    #endif

    return;
};

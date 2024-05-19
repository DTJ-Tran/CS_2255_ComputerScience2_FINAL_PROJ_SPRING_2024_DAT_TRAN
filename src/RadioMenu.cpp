#include "RadioMenu.h"

std::unique_ptr<sf::Clock> RadioMenu::timer = nullptr;
std::unique_ptr<CommentMenu> RadioMenu::sharingComment = nullptr;

RadioMenu::RadioMenu() : Menu() {
    setTitle("");
    setOption(std::vector<std::string>());
    setStation("");
    if (timer == nullptr) {
        timer = std::make_unique<sf::Clock>();
    };
    setSharingComment();
    setSpecifedComment("Null Community");
};


RadioMenu::RadioMenu(const std::string radioName, const std::string dataFolderPath) 
:Menu(radioName,{"Running Time: ", "Playing", "Pausing", "Shuffle", "Add New Music","Radio Info","Comment","Community Comment"}){
    setStation(dataFolderPath);
    if (timer == nullptr) {
        timer = std::make_unique<sf::Clock>();
    };
    setSharingComment();
    setSpecifedComment("Welcome to " + radioName + " Community");
    
};

void RadioMenu::setSharingComment() {
    this->sharingComment = std::make_unique<CommentMenu>();
    return;
};

CommentMenu& RadioMenu::getSharingComment() {
    return *(this->sharingComment);
};

void RadioMenu::setSpecifedComment(std::string inputTitle) {
    this->specifiedComment = std::make_unique<CommentMenu>(inputTitle);
    return;
};

CommentMenu& RadioMenu::getSpecifiedComment() {
    return *(this->specifiedComment);
}

RadioStation& RadioMenu::getDirrectStation() {
    return *station;
};

void RadioMenu::setStation(std::string dataFolderPath) {
    std::string stationName = this->getTitle();
    station = new RadioStation(stationName, dataFolderPath);
    return;
}

void RadioMenu::handleChoice(int choice) {
    std::string feedingFilePath = "";
    size_t length = 0;
    // Declare a flag to control the thread execution
   

    switch(choice){
        case PLAYING:  
            station->playThePlaylist();
            break;
        case PAUSING:
            station->pauseThePlaylist();
            break;
        case SHUFFLE:
            station->shufflePlayList();
            break;
        case ADD_NEW_MUSIC:
            #ifdef __APPLE__ 
            clear(); // clear all the menu 
            refresh(); // update the physical screen
            printw("%s \n", "Enter your new music file Path that you want to add to the Radio");

            char inputFilePath[256]; 
            echo();
            getstr(inputFilePath);
            noecho();
            length =strlen(inputFilePath);
            feedingFilePath = std::string(inputFilePath, length); // convert from c_string to std::string
            

            // check if the provided path is valid or not & is mp3 or not
            if(std::filesystem::exists(feedingFilePath) // Check if the file exists
                && std::filesystem::is_regular_file(feedingFilePath)  // Check if it's a regular file
            )
                {
                    // if the file is mp3 or not
                    if(std::filesystem::path(feedingFilePath).extension() == ".mp3") {
                        station->addNewMusicToList(feedingFilePath);
                        printw("%s\n", " New music added successfully");
                    } else {
                        printw("%s\n", "Improper format type - not mp3 file - system breakout" );
                        refresh();
                    }
                }
            else
                {
                    printw("%s \n","Not exist folder - system breakout");
                }
       
            break;
            #else
            system("cls");
            std::cout << "Enter your new music file Path that you want to add to the Radio" << std::endl;
            std::cin >> feedingFilePath;
            // check if the provided path is valid or not & is mp3 or not
            if(std::filesystem::exists(feedingFilePath)  // Check if it's a regular file
                && std::filesystem::is_regular_file(feedingFilePath)  // Check if it's a regular file
            )
                {
                    // if the file is mp3 or not
                    if(std::filesystem::path(feedingFilePath).extension() == ".mp3") {
                         station->addNewMusicToList(feedingFilePath);
                         std::cout << "New music added successfully" << std::endl;
                    } else {
                        std::cout << "Improper format type - not mp3 file - system breakout" << std::endl;
                    }
                }
            else
                {
                    std::cout << "Not exist folder - system breakout" << std::endl;
                }

            break;
            #endif
        case RADIO_INFO:
            station->showRadioInfo();
            break;
        case COMMENT: // go to the comment menu (while the music been played)
            sharingComment->runMenu();
            break;
        case COMMUNITY_COMMENT:
            specifiedComment->runMenu();
            break;
        default:
            std::cout << "Repress key again" << std::endl;
            break;
    }
    return;
}

void RadioMenu::toStringRunningTime() { // for Mac Platform - for the Window not ready 
        static int totalSeconds =0;
        static int hour = 0;
        static int minute = 0; 
        static int second = 0;
        totalSeconds = timer->getElapsedTime().asSeconds();
        // Calculate hours, minutes, and seconds
        hour = totalSeconds / 3600;
        totalSeconds %= 3600;
        minute = totalSeconds / 60;
        second = totalSeconds % 60;
        #ifdef _WIN32
            std::cout << "Elapsed time: " << std::setfill('0') << std::setw(2) << hour << "::"
            << std::setfill('0') << std::setw(2) << minute << "::"
            << std::setfill('0') << std::setw(2) << second << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1)); // clean after 1 sec
            std::cout << "\033[2K\r";

        #else
        if (initscr() != nullptr) // check if the ncurse screen been initalized (this line is difference )
            {   
                int maxRow =0;
                int maxCol = 0;
                getmaxyx(stdscr, maxRow, maxCol);
                printw("Elapsed time: %02d : %02d : %02d seconds\n", hour, minute,second);  // Display elapsed time  (at the certain time mark)
                move(getcury(stdscr) -1,0); //move(int y, int x)
                // move(maxRow-(getOption().size()+2),0);
                std::this_thread::sleep_for(std::chrono::seconds(1));
                clrtoeol(); // clear to end of line() - the current
                // refresh();
            };
        #endif
        return;
    };

void RadioMenu::displayMenu(int inputChoice) { // redefine for the range of option displaying
    std::string titleMessage = getTitle();
    std::vector<std::string> optionList = getOption();
    std::string instructionMessage = "Use arrow keys to navigate, press Enter to select, Esc to exit.";
   
    #ifdef _WIN32
        system("cls"); // Clear screen for Windows
        std::cout << titleMessage << std::endl;
    #else
        if (initscr() == nullptr) { // Initialize ncurses mode if the screen not been inited
            initscr();
        } 
        clear(); // Clear the screen in macOS (using ncurses)
    #endif
   
    #if __APPLE__
        int paddingLength = std::max(0, static_cast<int>(titleMessage.length()) - static_cast<int>(instructionMessage.length()));
        std::string padding(paddingLength, ' ');
        printw("%s%s\n", padding.c_str(), titleMessage.c_str()); // print the title message
    #endif

    for (int i = 1; i < optionList.size(); i++) {
        if (inputChoice == i) {
            #ifdef _WIN32
                std:: cout << " > " << optionList[i] << std::endl;
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
    printw("%s%s\n", padding.c_str(), instructionMessage.c_str());
    #endif

    return;
};

int RadioMenu::updateKeyBoardInput(int& theInput) { 
    
    #ifdef _WIN32
    auto start = std::chrono::steady_clock::now(); // Get the current time
    theInput = -1; // Initialize keyBoardInput

    while (true) {
        std::this_thread::sleep_for(std::chrono::microseconds(500)); // Wait for 0.5 sec
        theInput = _getch(); // Check for keyboard input

        // If a key is pressed or timeout occurs
        if (theInput != -1 || std::chrono::steady_clock::now() - start >= std::chrono::seconds(600)) {
            break; // Exit the loop
        }
    }

    // If no key is pressed within the timeout, set to null character
    if (theInput == -1) {
        theInput = '\0';
    }
    #else

    auto start = std::chrono::steady_clock::now(); // Get the current time
    theInput = ERR; // Initialize keyBoardInput

    while (true) {
        std::this_thread::sleep_for(std::chrono::microseconds(500)); // Wait for 0.5 sec
        theInput = getch(); // Check for keyboard input

        // If a key is pressed or timeout occurs
        if (theInput != ERR || std::chrono::steady_clock::now() - start >= std::chrono::seconds(600)) {
            break; // Exit the loop
        }
    }

    // If no key is pressed within the timeout, set to null character
    if (theInput == ERR) {
        theInput = '\0';
    }

    #endif

    return theInput;
};

void RadioMenu::runMenu() {
    int keyBoardInput = 0;
    int choice = 0; 
    int sizeMenu = getOption().size();
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

    #else
        do {
            cbreak(); // Line buffering disabled
            keypad(stdscr,TRUE); // Enable keypad mode for special keys
            noecho();
            // Launch async tasks for keyboard input and running time calculation
            std::future<void> toStringRunningTime = std::async(std::launch::async, &RadioMenu::toStringRunningTime, this);
            std::future<int> autoUpdateKeyBoardIn = std::async(std::launch::async, &RadioMenu::updateKeyBoardInput, this, std::ref(keyBoardInput));

            // Wait for either keyboard input or a timeout
            auto status = autoUpdateKeyBoardIn.wait_for(std::chrono::seconds(10));

            switch (keyBoardInput) {
                case '\0': // No key pressed
                    choice = (choice + sizeMenu) % sizeMenu;
                    break;
                case KEY_UP: // Up arrow
                    choice = (choice - 1 + sizeMenu) % sizeMenu;
                    break;
                case KEY_DOWN: // Down arrow
                    choice = (choice + 1) % sizeMenu;
                    break;
                case '\n': // Enter
                    handleChoice(choice);
                    printw("\nPress any key to continue...\n");
                    getch();
                    break;
                case 27: // Escape
                    endwin(); // End ncurses mode before exiting
                    return;
                default: // print the message and give 10 sec to exit -> else do the self break
                    printw("> %s\n", "Invalid input. Please try again - press anykey to choosing again");
                    getch();
                    break;
            }

            // Update menu based on user input
            std::thread updateThread(&RadioMenu::displayMenu, this, choice);

            // Wait for running time calculation to complete
            toStringRunningTime.wait();

            // Join the update thread and refresh the screen
            if (updateThread.joinable()) {
                updateThread.join();
            }
            refresh();

            // If user input is detected, continue to the next iteration
            if (status == std::future_status::ready) {
                continue;
            }

            // Sleep for a short duration to avoid busy waiting
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        } while (true);

        // End ncurses mode before exiting
        endwin();
    
    #endif

    return;
};


RadioMenu::~RadioMenu() {
    if(station != nullptr) {
        delete station;
    };
}
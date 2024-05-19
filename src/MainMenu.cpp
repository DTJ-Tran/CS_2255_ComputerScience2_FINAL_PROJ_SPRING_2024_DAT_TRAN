#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu() : Menu("Welcome to Radio App",{"R&B station", "Pop Station", "Lofi Station"}) {
    setRandB(getOption()[0],"");
    setPop(getOption()[1],"");
    setLofi(getOption()[2],"");
};

MainMenu::MainMenu(std::vector<std::string> listOfFolder)  
: Menu("Welcome to Radio App",{"R&B station", "Pop Station", "Lofi Station"}) {
    
        if (!listOfFolder.empty()) {
        setRandB(getOption()[0], listOfFolder[0]);
        setPop(getOption()[1], listOfFolder.size() > 1 ? listOfFolder[1] : "");
        setLofi(getOption()[2], listOfFolder.size() > 2 ? listOfFolder[2] : "");
        
        }
    };


void MainMenu::setRandB(const std::string RadioName, const std::string RandBFolderPath) {
    RandB = new RadioMenu(RadioName,RandBFolderPath);
    return;
    
    };

void MainMenu::setPop(const std::string RadioName, const std::string PopFolderPath) {
    Pop = new RadioMenu(RadioName, PopFolderPath);
    return;
    
    };

void MainMenu::setLofi(const std::string RadioName, const std::string LofiFolderPath) {
    Lofi = new RadioMenu(RadioName, LofiFolderPath);
    return;

    };

void MainMenu::handleChoice(int choice){

    switch (choice) {
        case R_AND_B:
            RandB->runMenu();
            break;
        case POP:
            Pop->runMenu();
            // rad2 = RadioMenu(optionList[1]);
            break;
        case LOFI:
            Lofi->runMenu();       
            // rad3 = RadioMenu(optionList[3]);
            break;
        default:
            std::cout << "Invalid choice. Please select again." << std::endl;
            break;
    };
};

MainMenu::~MainMenu()
    {
        if (RandB != nullptr)
            {
                delete RandB;
            }
        if (Pop != nullptr)
            {
                delete Pop;
            }
        if (Lofi != nullptr)
            {
                delete Lofi;
            }
    }

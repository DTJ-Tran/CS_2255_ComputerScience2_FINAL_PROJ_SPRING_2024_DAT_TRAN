#pragma once
#include<iostream>
#include<string>
#include<vector>

#ifdef _WIN32
    #include<windows.h>
    #include<conio.h>
#else // for Linus based system
    #include<ncurses.h>
#endif

class Menu {
    private:
         std::string title;
         std::vector<std::string> option;
    public:
        
        // const int volume1 = 1;

        Menu(const std::string&, const std::vector<std::string>&);  
        Menu();

        std::string getTitle() const;
        void setTitle(const std::string&);

        std::vector<std::string> getOption() const; // for indirrect access with the private property
        void setOption(const std::vector<std::string>&);

        virtual void displayMenu(int); 

        virtual void handleChoice(int) = 0; // different handling (diferent method)

        void runMenu(); // same
};
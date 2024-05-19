// MainMenu.h
#pragma once
#include "Menu.h"
#include "RadioStation.h"
#include "RadioMenu.h"

class MainMenu : public Menu {

private:
    static constexpr int R_AND_B = 0;
    static constexpr int POP = 1;
    static constexpr int LOFI = 2;
    RadioMenu* RandB;
    RadioMenu* Pop;
    RadioMenu* Lofi;
public:
   
    void setRandB(const std::string, const std::string);
    void setPop(const std::string, const std::string);
    void setLofi(const std::string, const std::string);
    MainMenu();
    MainMenu(const std::vector<std::string>);
    void handleChoice(int) override;
    ~MainMenu();
};



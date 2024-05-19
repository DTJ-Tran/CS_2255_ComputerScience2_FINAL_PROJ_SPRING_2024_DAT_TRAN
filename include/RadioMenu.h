#pragma once
#include "Menu.h"
#include "RadioStation.h"
#include<thread>
#include<chrono>
#include <iomanip>
#include<SFML/Audio.hpp>
#include<iostream>
#include<future>
#include<cstring>
#include"CommentMenu.h"
#include<memory>

class RadioMenu: public Menu{
    private:
        RadioStation* station;
        static constexpr int PLAYING = 1;
        static constexpr int PAUSING = 2;
        static constexpr int SHUFFLE = 3;
        static constexpr int ADD_NEW_MUSIC = 4;
        static constexpr int RADIO_INFO = 5;
        static constexpr int COMMENT = 6;
        static constexpr int COMMUNITY_COMMENT = 7;

        static std::unique_ptr<CommentMenu> sharingComment;
        std::unique_ptr<CommentMenu> specifiedComment;
        
        static std::unique_ptr<sf::Clock> timer;
    public:
        

        RadioMenu();
        RadioMenu(const std::string, const std::string);
        ~RadioMenu();
        RadioStation& getDirrectStation();
        void setStation(std::string);
        virtual void handleChoice(int);
        void toStringRunningTime();
        int updateKeyBoardInput(int&);
        void displayMenu(int);
        void runMenu();
        void setSharingComment();
        CommentMenu& getSharingComment();
        void setSpecifedComment(std::string);
        CommentMenu& getSpecifiedComment();
};
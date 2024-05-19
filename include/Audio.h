#pragma once
#include<SFML/Audio.hpp>
#include<iostream>
#include<algorithm>
#include<string>
#include"VolumeAdjust.h"
#include<memory>
#ifdef __APPLE__
    #include<ncurses.h>
#endif



class Audio{
    
    private:
        std::string audioFileName;
        sf::Sound music;
        sf::SoundBuffer musicBuffer;
        std::unique_ptr<sf::Clock> timer;
        
        

    public:
        Audio();
        Audio(std::string const);

        sf::Clock getTimer() const;
        void setTimer();
        
        std::string getMusicFile() const  ;
        void setMusicFile(const std::string);

        sf::SoundBuffer& getMusicBuffer();

        sf::Sound& getMusicObject();

        
        void setMusic();
       void playMusic();

        void pauseMusic();
        void loopControl(); // For replay that song again

        void volumeStaticAdjust(float);  // adjust the Volume by taking an int

        float getCurrentVol() const ; // get the current vol level of the buffer

        void audioTransition(Audio*, float);

        ~Audio();
        
};

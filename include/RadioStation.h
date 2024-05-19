// #include "RadioMenu.h"
#pragma once
#include "Audio.h"
#include<filesystem>
#include<fstream>
#include<vector>
#include<string>
#include<atomic>
#include<mutex>




class RadioStation {

    private:
        std::vector<std::string> listOfMusicFile; // read from the folder the playlist of music file
        std::vector<Audio*> thePlaylist;
        int numberOfPlay;
        static float VolumeLevel; // stay when the class still exist
        std::string RadioName;

        std::thread playingThread;
        // Declare a mutex for synchronization
        std::mutex playlistMutex;
        std::atomic<bool> isPaused; // New atomic variable to indicate whether the playlist is paused   

    public:

        RadioStation(std::string&, std::string&);
        RadioStation();
        
        std::string getRadioName() const;
        void setRadioName(std::string);

        //Non playable object
        std::vector<std::string> getMusicList() const ;
        void setMusicList(std::string) ;

        // get dirrectly the musicList:
        
        std::vector<std::string>& getDirrectMusicList();

        //Playable (create a copy)
        std::vector<Audio*> getPlayList() const ;

        // pass by ref return:
        std::vector<Audio*>& getDirrectPlaylist();


        // Setter accept a reference
        void setPlayList(std::vector<std::string>);

        void setVolume(const float);
        float getVolume() const;

        void setPlayingTimes(int);
        int getPlayingTimes() const;
        void updatePlayingTime();

     
        void shufflePlayList();

        void addNewMusicToList(std::string);

        void playThePlaylist();
        void pauseThePlaylist();
        void showRadioInfo();

        ~RadioStation(); // need to check the Audio object in the heap is being deleted or not
        
        
};
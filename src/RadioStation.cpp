#include "RadioStation.h"
#include "Audio.h"
#include<random>
#ifdef __APPLE__
    #include<ncurses.h>
#endif

float RadioStation::VolumeLevel = 50.0f;


void RadioStation::setRadioName(std::string inputName) {
    RadioName = inputName;
    return;
    };

std::string RadioStation::getRadioName() const {
    return RadioName;
    };

void RadioStation::setPlayingTimes(int updatePlayingTime) {
    numberOfPlay = updatePlayingTime;
    return;
    };

int RadioStation::getPlayingTimes() const {
        return numberOfPlay;
    };

void RadioStation::setVolume(const float VolSet) {
        VolumeLevel = VolSet;
        return;
    };

void RadioStation::updatePlayingTime() {
    this->setPlayingTimes(this->getPlayingTimes()+1);
    return;
}

float RadioStation::getVolume() const {
        return this->VolumeLevel;
    };

// holding file data -> music file (read from the folder)
void RadioStation::setMusicList(std::string audioFolderAddrress) {

        std::vector<std::string> audioFileList = std::vector<std::string>();
        
        // check if the folder exist:
        if (std::filesystem::exists(audioFolderAddrress) && std::filesystem::is_directory(audioFolderAddrress)) {
            // Iterate over each file in the folder
                for (const auto& entry : std::filesystem::directory_iterator(audioFolderAddrress)) {
                    if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
                        audioFileList.push_back(entry.path().string());
                    }
                    
                }
            } else {
                std::cerr << "Folder not found or is not a directory." << std::endl;
            };

        listOfMusicFile = audioFileList;
        listOfMusicFile.shrink_to_fit();
        return;
    };

std::vector<std::string> RadioStation::getMusicList() const  {
        return listOfMusicFile;
    };

// get dirrectly from the memory the musicList

std::vector<std::string>& RadioStation::getDirrectMusicList() {
    return listOfMusicFile;
};

// Playable object -> which create sound
void RadioStation::setPlayList(std::vector<std::string> listOfFile) {
    // getDirrectPlaylist().clear(); // Clear existing playlist
    for (int iter = 0; iter < listOfFile.size(); iter++) {
        // std::unique_ptr<Audio> musicPtr(new Audio(listOfFile[iter])); // storing in heap
        Audio* musicPtr = new Audio(listOfFile[iter]);
        getDirrectPlaylist().push_back(std::move(musicPtr)); // Move ownership to the playlist
    }
    return;
    };

std::vector<Audio*> RadioStation::getPlayList() const {
    return this->thePlaylist;
    };

std::vector<Audio*>& RadioStation::getDirrectPlaylist() {
       
        return this->thePlaylist;
    };

void RadioStation::shufflePlayList() {
   
    #ifdef __APPLE__
        if (initscr() == nullptr) { // Initialize ncurses mode if the screen not been inited
            initscr();
            } 
    #endif

    std::vector<Audio*>& shufList = getDirrectPlaylist(); // pass by ref first
    if (getPlayList().empty()) {
        #ifdef _WIN32
        std::cout << "Empty plalist, nothing to swap been shuffled" << std::endl;
        #else
        printw("> %s\n", "Empty plalist, nothing to swap been shuffled");
        #endif

        return; // nothing to swap
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    int lastElement = shufList.size() -1;
    for (unsigned int iter = 0; iter < shufList.size(); ++iter)
        {   
            std::uniform_int_distribution<unsigned int> distribution (iter, (lastElement));
            unsigned int jter = distribution(gen);
            std::swap(shufList[iter], shufList[jter]);
        }
        #ifdef __APPLE__
            printw("%s\n", "Playlist been shuffled");
        #else
        std::cout << "Plalist been shuffled" << std::endl;
        #endif
    return;

    };

void RadioStation::addNewMusicToList(std::string newMusicFile) {
        std::vector<std::string>& dirrectMusicList = getDirrectMusicList();
        dirrectMusicList.push_back(newMusicFile);

        // auto update the playlist
        std::vector<Audio*>& thePlayList = getDirrectPlaylist();
        thePlaylist.push_back(new Audio(dirrectMusicList.back())); // Create a new Audio object and move it into the vector
    };

void RadioStation::playThePlaylist() {

        std::vector<Audio*>& workingPlaylist = this->getDirrectPlaylist(); 
        std::lock_guard<std::mutex> lock(playlistMutex);
        this->updatePlayingTime(); // 1 clicking time of playing -> add 1 to the playing times

        if (workingPlaylist.empty()) {
            #ifdef __APPLE__
            printw("%s", "Play nothing, empty playlist");
            #else
            std::cout << "Play nothing, empty playlist" << std::endl;
            #endif
            return; // Early exit if the playlist is empty
        }
        isPaused.store(false);
        auto musicControl = [&]() {
            for (int iter = 0; iter < workingPlaylist.size(); iter++) {
            if (isPaused.load())
                {
                    workingPlaylist[iter]->pauseMusic();
                    return;
                }
            else 
                {
                    workingPlaylist[iter]->playMusic();
                    // Wait for the current music to finish playing
                    while (workingPlaylist[iter]->getMusicObject().getStatus() == sf::Sound::Playing) {
                    if (isPaused.load()) {
                        workingPlaylist[iter]->pauseMusic();
                        return;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                
                }
            }
            
            
        };

        playingThread = std::thread(musicControl);

            if (playingThread.joinable()) {
                playingThread.detach();
            }  
        return;
    };

void RadioStation::pauseThePlaylist() {
    isPaused.store(true);
    #ifdef __APPLE__
        printw("%s\n", "Music has stopped");
    #else
        std::cout <<  "Music has stopped" << std::endl;
    #endif

    return;
    };

void RadioStation::showRadioInfo() // need to notice on displaying
    {
        #ifdef __APPLE__
            int updateTime = getPlayingTimes();
            refresh();
            printw("%s %d \n", "The radio has been played: ",updateTime);
            printw("%s %s", "Categories: ", getRadioName().c_str());
        #else
            std::cout << "The radio has been played: " << getPlayingTimes() << " " << std::endl;
            std::cout << "Categories: " << RadioName << " " << std::endl;
        #endif
        return;
    };

RadioStation::RadioStation(std::string& RadioName, std::string& audioFolderAddrress) // each radio has own folder 
    {
        this->setRadioName(RadioName);
        this->setMusicList(audioFolderAddrress);
        this->setPlayList(this->getDirrectMusicList());
        this->setPlayingTimes(0);
        this->setVolume(50); // initally always 50
        this->isPaused = true; // set the playlist currently paused
    };

RadioStation::RadioStation()
    {
        this->setRadioName("");
        // this->setMusicList(""); // set the list of file getFrom folder
        this->setPlayList(std::vector<std::string>()); // set the list of Audio
        this->setPlayingTimes(0);
        this->setVolume(50);
        this->isPaused = true; // set the playlist currently paused

    };

RadioStation::~RadioStation() {

   
    return;
    };

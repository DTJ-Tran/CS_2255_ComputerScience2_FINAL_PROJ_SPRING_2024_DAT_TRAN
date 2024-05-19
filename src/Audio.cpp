#include "Audio.h"
#include "VolumeAdjust.h"

    Audio::Audio(std::string const fileName){

        this->setMusicFile(fileName);
        this->setMusic();
        this->setTimer();
        return;
    };

    Audio::Audio() {
        setMusicFile("");
        return;
    }
    
    Audio::~Audio() {
    };
    
    sf::Clock Audio::getTimer() const {
        return *this->timer;
    };

    void Audio::setTimer() {

        this->timer = std::make_unique<sf::Clock>();
        (this->timer)->restart();
        return;
    };

    void Audio::setMusicFile(const std::string inputMusicFile) {

        audioFileName = inputMusicFile;
        return;
    };

    std::string Audio::getMusicFile() const {

        return audioFileName;
    }

    sf::SoundBuffer& Audio::getMusicBuffer() {
        return this->musicBuffer;
    }
   
    sf::Sound& Audio::getMusicObject() {
        return music;
    }

    void Audio::setMusic() {

        if (!musicBuffer.loadFromFile(getMusicFile())) {
            std::cerr << "Error in loading sound file !" << std::endl;
            return;
        };
        this->music.setBuffer(musicBuffer);
        return;

    };

    void Audio::playMusic(){

        if(music.getStatus()!=sf::Music::Playing) {
             this->music.play();
        }
        this->setTimer();
          
        return;
    };

    void Audio::pauseMusic(){

        this->music.pause();
        return;
    };

    void Audio::loopControl() { // set 1 specific song to loop

        if (music.getLoop()==true) {
            this->music.setLoop(false);
        }
        else {
            this->music.setLoop(true);
        }
        return;
    };
    // For replay that song again
 
    void Audio::volumeStaticAdjust(float targetVolume) {

        this->music.setVolume(targetVolume);
        return;
    };

    float Audio::getCurrentVol() const  {
        return music.getVolume();
    };

   void Audio::audioTransition(Audio* theNextAudio, float transitionTimeSeconds) {

        // Check if the next Audio has a valid music file
        std::string nextMusicFile = theNextAudio->getMusicFile();
        if (nextMusicFile.empty()) {
            std::cerr << "Next Audio does not have a valid music file" << std::endl;
            return;
        }

        // Check if the next Audio's music buffer is loaded successfully
        const sf::SoundBuffer& nextMusicBuffer = theNextAudio->getMusicBuffer();
        if (nextMusicBuffer.getDuration().asSeconds() <= 0.0f) {
            std::cerr << "Failed to load music buffer for the next Audio" << std::endl;
            return;
        }

        // get the Duration of the first Audio to measure the time:
        sf::Time durationAsSec = this->getMusicBuffer().getDuration();


        // Start fading out the first audio file
        sf::Time fadeOutTime = sf::seconds(transitionTimeSeconds /2.0f);
        sf::Time elapsedTime = this->getTimer().getElapsedTime();

        double targetVolume = 0.0;  // Target volume level (absolute zero)
        double smoothingFactor = 0.1; // Smoothing factor (adjust as needed)
        double stepSize = 0.1; // Step size for each adjustment
        double zeroThreshold = 0.1; // Threshold for rounding to zero
        double oneThreshold = 0.1; // Threshold for rounding to one

        double theCurrentVol = this->getCurrentVol()/100.0;
        volumeAdjust adjuster = volumeAdjust();

        sf::Time targetingTime = durationAsSec - fadeOutTime; // before reach the mile need to fadeOut

        // gradually adjustVolume (adjust till end || adjust till the audio reach mute)

        // check elasped Time run to the targeting time or not
        while (elapsedTime <= targetingTime) // not reach the time to adjust the volume (keeap runing)
            {
                elapsedTime = this->getTimer().getElapsedTime(); // Re-update the timer
            }
        
        while ((elapsedTime < durationAsSec) || (std::abs(theCurrentVol - targetVolume) >= 0.01)) {
                    theCurrentVol = adjuster.adjustVolume(theCurrentVol, targetVolume,smoothingFactor, zeroThreshold, oneThreshold);
                    this->volumeStaticAdjust(theCurrentVol*100);
                    sf::sleep(sf::milliseconds(100)); // Adjust this sleep time as needed for smoother transitions
                    elapsedTime = this->getTimer().getElapsedTime(); // Re-update the timer
                        
                }
       
        if (this->getCurrentVol() == 0) 
            {
                this->pauseMusic();
            }
        sf::Sound& nextMusic = theNextAudio->getMusicObject();
        nextMusic.setVolume(50);
        nextMusic.play();

        // Wait for the second audio file to finish playing
        while (nextMusic.getStatus() == sf::Sound::Playing) {
             sf::sleep(sf::milliseconds(100)); // Adjust this sleep time as needed for smoother transitions
        }

        // clean up
        nextMusic.stop();

        return;
    };

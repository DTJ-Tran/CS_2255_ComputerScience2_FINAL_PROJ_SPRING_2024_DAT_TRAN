#include"Audio.h"
#include"Comment.h"
#include"CommentMenu.h"
#include"RadioStation.h"
#include"RadioMenu.h"
#include "MainMenu.h"

int main() {

   
    // Get the current working directory
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::vector<std::string> folderVector;
    folderVector.push_back((currentPath / "testingAudio/RandB").string());
    folderVector.push_back((currentPath / "testingAudio/Pop").string());
    folderVector.push_back((currentPath / "testingAudio/Lofi").string());

    MainMenu tesingMainMenu = MainMenu(folderVector);
   
    tesingMainMenu.runMenu();
    return 0;
}
//  g++ --std=c++17 source.cpp Comment.cpp CommentMenu.cpp MainMenu.cpp RadioMenu.cpp RadioStation.cpp Audio.cpp Menu.cpp VolumeAdjust.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -o source -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-audio -lsfml-system -lncurses -g

// rewrite the dynamic volume adjust


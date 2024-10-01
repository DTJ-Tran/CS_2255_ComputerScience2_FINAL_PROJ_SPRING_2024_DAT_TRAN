# CS_2255_ComputerScience2_FINAL_PROJ_SPRING_2024_DAT_TRAN

# Radio Station Service

This project is an audio player application developed using C++ with SFML for handling music playback. It includes various classes such as Audio, Comment, CommentMenu, MainMenu, Menu, RadioMenu, RadioStation, VolumeAdjust, and their respective implementations in the source code.


## Deployment

Use the git clone command followed by the URL of the repository 


```bash
  git clone https://github.com/DTJ-Tran/CS_2255_ComputerScience2_FINAL_PROJ_SPRING_2024_DAT_TRAN

```
Move to buid folder in the gitclone File
```bash
  cd build
```
Building the project 
```bash
cmake ..
```
After Building, move into Debug Folder 
```bash
cd Debug
```
Run the exe File:
```bash
./TeamProjectFinal (for MacOS)
```

With the MacOS user (you should have install cmake and using VS Studio Code)

```bash
  git clone https://github.com/DTJ-Tran/CS_2255_ComputerScience2_FINAL_PROJ_SPRING_2024_DAT_TRAN

```

Move to buid folder in the gitclone File
```bash
  cd build
```

```bash
  camke ...
```

```bash
  make
```

```bash
  ./TeamProjectFinal (for MacOS)
```

## Features
Audio Class: Manages audio playback functionality.

Comment Class: Represents comments associated with audio files.

CommentMenu Class: Inherits from Menu class and provides a menu for managing comments.

MainMenu Class: Inherits from Menu class and provides the main menu interface.

Menu Class: Abstract base class for creating menu interfaces.

RadioMenu Class: Inherits from Menu class and provides a menu for managing radio stations.

RadioStation Class: Represents radio stations and handles backend functionality.

VolumeAdjust Class: Manages volume adjustment for audio playback.

## Dependencies
SFML: Simple and Fast Multimedia Library for handling audio playback. 

(Version 2.6.x is required (on the Github version we have include the lib in the Debug folder both in build folder for each platform you use))

CMake: Build automation tool for generating platform-specific build files.

ncures (For macOS)


## Projct Contribution:

Dat Tran Tien (Develope on MacOS platform - project leader)

Nguyen Hai An (Develope on Window platform - project member)

Nguyen Kim Tuan Cuong (Tester, Project Reporter - Support on Window platform - Project member)


## License

This Project is following on MIT License.

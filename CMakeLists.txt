cmake_minimum_required(VERSION 3.10)
project(TeamProjectFinal)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

if(WIN32)
    set(SFML_DIR "lib/cmake/SFML")
    find_package(SFML 2.6 COMPONENTS system audio REQUIRED)
elseif(APPLE)
    # Find SFML package
    find_package(SFML 2.6 COMPONENTS system audio REQUIRED)

    # Find ncurses package
    find_package(Curses REQUIRED)

    # Include ncurses directories
    include_directories(${CURSES_INCLUDE_DIR})
endif()
# List all source files
set(SOURCES
    src/Audio.cpp
    src/Comment.cpp
    src/CommentMenu.cpp
    src/MainMenu.cpp
    src/Menu.cpp
    src/RadioMenu.cpp
    src/RadioStation.cpp
    src/source.cpp
    src/VolumeAdjust.cpp
)

# Add executable target
add_executable(TeamProjectFinal ${SOURCES})

# Link SFML and ncurses libraries
target_link_libraries(TeamProjectFinal sfml-system sfml-audio ${CURSES_LIBRARIES})



# Copy the testingAudio directory to the build directory
add_custom_command(
    TARGET TeamProjectFinal POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/src/testingAudio"
    "$<TARGET_FILE_DIR:TeamProjectFinal>/testingAudio"
    COMMENT "Copying testingAudio directory to the build directory"
)
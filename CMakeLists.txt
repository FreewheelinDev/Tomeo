cmake_minimum_required(VERSION 3.23)
project(FreeWheelingProject)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# set to use deprecated apis


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        MultimediaWidgets
        REQUIRED)

add_executable(videoPlayer
        the_button.cpp
        the_button.h
        the_player.cpp
        the_player.h
        tomeo.cpp)

target_link_libraries(videoPlayer
        Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets)
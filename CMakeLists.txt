cmake_minimum_required(VERSION 3.23)
project(FreeWheelingProject)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt@5/5.15.7")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        MultimediaWidgets
        REQUIRED)

add_executable(Tomeo
        the_player.cpp
        the_player.h
        the_button.cpp
        the_button.h
        tomeo.cpp MainWindow.cpp MainWindow.h MainWindow.ui)

target_link_libraries(Tomeo
        Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets)

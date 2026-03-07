cmake_minimum_required(VERSION 3.18)
project(QT)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 COMPONENTS
        Widgets Multimedia
        REQUIRED)

set(WIN_RESOURCES logo.rc)

add_executable(Spaceship WIN32 ressource.qrc logo.rc
        Projet/src/main.cpp
        Projet/src/MainWindow.cpp
        Projet/src/Menu.cpp
        Projet/src/GameOver.cpp
        Projet/src/GameScene.cpp
        Projet/src/Shoot.cpp
        Projet/src/SpaceShip.cpp
        Projet/src/Life.cpp
        Projet/src/Score.cpp
        Projet/src/Enemies.cpp
        Projet/src/Asteroid.cpp
        Projet/src/Bonus.cpp
        Projet/src/Musique.cpp
        Projet/src/Boss.cpp)

target_link_libraries(Spaceship Qt6::Widgets Qt6::Multimedia)
    
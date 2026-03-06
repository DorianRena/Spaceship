# Guide d'installation de Spaceship

Ceci est un guide fait en 2026 suite à la création de ce jeu à défilement vertical avec rcollo25 en 2023.

## Installation sous Debian

Installer QT (il y aurait surement d'autres lib à installer) :
```bash
sudo apt install qt6-base-dev
```

Build l'app en utilisant l'ancien CMakeLists (en le renommant) :

```bash
mkdir build
cd mkdir
cmake ..
make
./Spaceship
```
Il y aura surement des prbls de stockage du score


## Installation sous Windows

Installer QT pour Windows : 
https://doc.qt.io/qt-6/qt-online-installation.html
(oui il faut créer un compte... )

Cliquer sur "Personnaliser l'installation" puis cocher la case : 

*Qt -> Qt 6.10.2 -> MSVC 2022 64-bit*

Puis build le ".exe" :

```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="C:/QT/6.10.2/msvc2022_64"   
cmake --build . --config Debug  
C:\QT\6.10.2\msvc2022_64\bin\windeployqt.exe Debug\Spaceship.exe
Copy-Item ..\Projet\other\Score.csv Debug
```

Lancer le ".exe" du jeu et have fun !
## To build the installer with MSBUILD, do the following steps
* Build the game using instructions from game/README.md file
* Build the installer using __msbuild Game.Installer.Msi.sln /p:Configuration=Release__ command

## To run the program go to installation folder, do the following
* Set the desired ships configuration for the game inside __map.txt__
* Run __battleship++.exe__ as administrator (administrator mode needed for sqlite to be able to create its database)
## To build the installer with MSBUILD, run the following command
* msbuild Game.Installer.Msi.sln /p:Configuration=Release

# To run the program go to installation folder and do the following
* Set your nickname inside __app-config.json__ 
* Set the desired ships configuration for the game inside __map.txt__
* Run __battleship++.exe__ as administrator (administrator mode needed for sqlite to be able to create its database)
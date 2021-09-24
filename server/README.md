## Description
This is a TCP server implementation in C#, it will be used to connect two players and forward traffic between them, it can be deployed, for example, to Azure Cloud, have a static public IP address, so that that different players can play with each other on the internet.

## To build the project with and run it, use the following step
* Install [.Net](https://dotnet.microsoft.com/download) on your machine
* Build the project using __dotnet build Battleship.Server.csproj --configuration=Release__ command
* Go to __bin\Release\net5.0\__ and start __Battleship.Server.exe__ file
* The server will start on localhost, port 5000, you can use these values inside C++ game config __game\app-config.json__ file
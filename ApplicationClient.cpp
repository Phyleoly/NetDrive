// ApplicationClient.cpp
#include <iostream>
#include <string>
#include "include/Command.h"
#include "include/Client.h"
#include "include/File.h"


// class ApplicationClient
// {
// private:
//     Client *client;
//     std::string cacheDir;

// public:
//     ApplicationClient(Client *client, std::string cacheDir) : client(client), cacheDir(cacheDir){};
//     ~ApplicationClient();
// };

// void init()
// {

//     ClientManager clientManager;

//     clientManager.createClient("TCP", "127.0.0.1", 4396);

//     std::cout << "connect success!" << std::endl;
// }



int main()
{
    std::string input;
    CommandParser commandParser;
    CommandExecutor commandexecutor;
    ClientManager clientManager;
    ThreadPool threadPool(10);

    // threadPool.addTask([&client]()
    //                    { client.connectByIp("127.0.0.1", 8080); });
    
    clientManager.createClient("UDP", "127.0.0.1", 12348);
    clientManager.connectClient(0);
    // clientManager.sendData(0, "Hello");
    while (true)
    {
        std::cout << ">";
        std::getline(std::cin, input);
        Command *command = commandParser.parseCommand(input);
        commandexecutor.executeCCommand(command, clientManager);
    }
    
    clientManager.disconnectClient(0);
    return 0;
}
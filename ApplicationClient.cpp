// ApplicationClient.cpp

#include <iostream>
#include <string>
#include "include/File.h"
#include "include/Command.h"
#include "include/ThreadPool.h"
#include "include/Client.h"


int main()
{
    std::string input;
    CommandParser commandParser;
    CommandData commandData;
    // ClientManager clientManager;

    commandData.ifServer=0;
    ThreadPool threadPool(10);

    // threadPool.addTask([&client]()
    //                    { client.connectByIp("127.0.0.1", 8080); });
    
    // clientManager.createClient("UDP", "127.0.0.1", 12348);
    // clientManager.connectClient(0);
    // clientManager.sendData(0, "Hello");
    while (true)
    {
        std::cout << ">";
        std::getline(std::cin, input);
        Command *command = commandParser.parseCommand(input);
        UDPClient udpClient;
        udpClient.setIpAddress("127.0.0.1");
        udpClient.setPort(8999);

        commandData.messageClient = &udpClient;
        udpClient.connectServer();
        command->execute(&commandData);
    }
    
    // clientManager.disconnectClient(0);
    return 0;
}
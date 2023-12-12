#include "include/ThreadPool.h"
#include  "include/Command.h"
#include "include/Server.h"
#include "include/File.h"
#include "include/Client.h"

int main()
{

    std::cout<<4;
    ThreadPool threadPool(4);
    std::cout<<3;
    CommandData commandData;


    FileSystem fileSystem;

    fileSystem.initialize();

    commandData.fileSystem = &fileSystem;
    commandData.port = 8999;

    std::cout<<5;
    while (1)
    {
        threadPool.addTask([&commandData] {
            std::string messageData;CommandParser commandParser;Protocol protocol;
            UDPServer messageServer;

            messageServer.setport(commandData.port);
            messageServer.start();

           messageServer.receiveData(messageData);
            std::cout<<messageData;
            Command *command = protocol.parseProtocolString(messageData);command->execute(&commandData); 
            messageServer.stop();
            });
    }
            
    // // serverManager.stopServer(0);
    // // TCPServer server;
    // // server.setport(12347);
    // // server.start();
    // // std::string data;
    // // server.receiveData(data);
    // // std::cout<<std::endl<<data<<std::endl;
    return 0;
}
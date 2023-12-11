#include "include/ThreadPool.h"
#include  "include/Command.h"
#include "include/Server.h"

int main()
{

    ThreadPool threadPool(4);

    CommandData commandData;

    CommandParser commandParser;

    FileSystem fileSystem;
    fileSystem.initialize();

    commandData.fileSystem = &fileSystem;
    commandData.port = 8999;

    while (1)
    {
        threadPool.addTask([&commandData] {
            std::string messageData;CommandParser commandParser;Protocol protocol;
            UDPServer messageServer;

            messageServer.setport(commandData.port);
            messageServer.start();
            messageServer.receiveData(messageData);
            Command *command = protocol.parseProtocolString(messageData);command->execute(&commandData); });
    }

    // serverManager.stopServer(0);
    // TCPServer server;
    // server.setport(12347);
    // server.start();
    // std::string data;
    // server.receiveData(data);
    // std::cout<<std::endl<<data<<std::endl;
    return 0;
}
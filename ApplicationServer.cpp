#include "include/Server.h"

int main()
{
    ServerManager serverManager;
    serverManager.createServer("UDP", 12348);
    serverManager.startServer(0);
    while (true)
    {
        std::string data;
        serverManager.receiveData(0, data);
        std::cout << data;
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
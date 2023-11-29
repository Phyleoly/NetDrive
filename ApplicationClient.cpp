// ApplicationClient.cpp

#include "include/Client.h" // 包含客户端的头文件
#include "include/Server.h"
#include <string>

class ApplicationClient
{
private:
    Client *client;
    std::string cacheDir;

public:
    ApplicationClient(Client *client, std::string cacheDir) : client(client), cacheDir(cacheDir){};
    ~ApplicationClient();
};

void init()
{
    TCPClient client;
    std::string ipAddress = "127.0.0.1";
    int port = 4396;

    ApplicationClient applicationClient(&client, "cache/");

    
    std::cout << "connect success!" << std::endl;
}

int main()
{

    return 0;
}
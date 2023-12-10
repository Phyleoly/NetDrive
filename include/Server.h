#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Command.h"

// 定义一个抽象的Server类
class Server
{
public:
    virtual void start() = 0;
    virtual void receiveData(std::string &data) = 0;
    virtual void receiveLargeData(char *largeData, int dataSize) = 0;
    virtual void sendData(const std::string &data) = 0;
    virtual void sendLargeData(const char *largeData, int dataSize) = 0;
    virtual void stop() = 0;
    std::string getipAddress();
    int getport();
    void setport(int port) { this->port = port; }

protected:
    int serverSocket;
    int clientSocket;
    sockaddr_in serverAddress{};

private:
    std::string ipAddress; // IP地址
    int port;              // 端口号
    bool isConnected;      // 是否已连接
};

// 定义一个具体的TCPServer类，继承自抽象的Server类
class TCPServer : public Server
{
public:
    void start() override;
    void receiveData(std::string &data) override;
    void receiveLargeData(char *largeData, int dataSize) override;
    void sendData(const std::string &data) override;
    void sendLargeData(const char *largeData, int dataSize) override;
    void stop() override;
};

// 定义一个具体的UDPServer类，继承自抽象的Server类
class UDPServer : public Server
{
public:
    void start() override;
    void receiveData(std::string &data) override;
    void receiveLargeData(char *largeData, int dataSize) override{};
    void sendData(const std::string &data) override;
    void sendLargeData(const char *largeData, int dataSize) override{};
    void stop() override;

private:
    sockaddr_in clientAddr;
};

class ServerManager
{
public:
    void createServer(const std::string &serverType, int port);
    void deleteServer(int index);
    Server *getServer(int index);
    void startServer(int index);
    void stopServer(int index);
    void receiveData(int index, std::string &data);
    void receiveLargeData(int index, char *largeData, int dataSize);
    void sendData(int index, const std::string &data);
    void sendLargeData(int index, const char *largeData, int dataSize);
    int getServerCount();

    void registerServer(ServerConfig* serverConfig);

private:

    std::vector<Server *> servers; // 服务器对象列表
};

#endif
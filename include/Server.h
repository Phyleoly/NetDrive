#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <vector>

// 定义一个抽象的Server类
class Server
{
public:
    virtual void start() = 0;
    virtual void receiveData(const std::string &data) = 0;
    virtual void sendData(const std::string &data) = 0;
    virtual void stop() = 0;
    std::string getipAddress();
    int getport();

protected:
    int serverSocket;
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
    void receiveData(const std::string &data) override;
    void sendData(const std::string &data) override;
    void stop() override;
};

// 定义一个具体的UDPServer类，继承自抽象的Server类
class UDPServer : public Server
{
public:
    void start() override;
    void receiveData(const std::string &data) override;
    void sendData(const std::string &data) override;
    void stop() override;
};

// 定义一个ServerManager类，用于管理Server对象
class ServerManager
{
private:
    std::vector<Server *> servers;

public:
    void addServer(Server *server);
    void removeServer(Server *server);
    void startAll();
    void receiveDataAll(const std::string &data);
    void sendDataAll(const std::string &data);
    void stopAll();
};

#endif
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>
#include <cstring>

class Client
{
public:
    virtual void connectByIp(const std::string &ipAddress, int port) = 0;
    virtual void sendData(const std::string &data) = 0;
    virtual void sendLargeData(const char *largeData, int dataSize) = 0;
    virtual void receiveData(std::string &data) = 0;
    virtual void receiveLargeData(std::vector<char> &largeData, int dataSize) = 0;
    virtual void disconnect() = 0;
    std::string getIpAddress() { return ipAddress; }
    int getPort() { return port; }
    void setIpAddress(std::string ipAddress) {this->ipAddress = ipAddress;}
    void setPort(int port) {this->port = port;}
protected:
    int clientSocket;

private:
    std::string ipAddress; // IP地址
    int port;              // 端口号
    bool isConnected;      // 是否已连接
};

// 定义一个具体的TCPClient类，继承自抽象的Client类
class TCPClient : public Client
{
public:
    void connectByIp(const std::string &ipAddress, int port) override;
    void sendData(const std::string &data) override;
    void sendLargeData(const char *largeData, int dataSize) override;
    void receiveData(std::string &data) override;
    void receiveLargeData(std::vector<char> &largeData, int dataSize) override;
    void disconnect() override;
};

// 定义一个具体的UDPClient类，继承自抽象的Client类
class UDPClient : public Client
{
public:
    void connectByIp(const std::string &ipAddress, int port) override;
    void sendData(const std::string &data) override;
    void sendLargeData(const char *largeData, int dataSize) override {};
    void receiveData(std::string &data) override;
    void receiveLargeData(std::vector<char> &largeData, int dataSize) override {};
    void disconnect() override;

private:
    sockaddr_in serverAddr{};
};

class ClientManager
{
public:
    void createClient(const std::string &clientType, const std::string &ipAddress, int port);
    void deleteClient(int index);
    Client *getClient(int index);
    void connectClient(int index);
    void disconnectClient(int index);
    void sendData(int index, const std::string &data);
    void sendLargeData(int index, const char *largeData, int dataSize);
    void receiveData(int index, std::string &data);
    void receiveLargeData(int index, std::vector<char> &largeData, int dataSize);
    int getClientCount();
    int findClientIndexByIp(const std::string &ipAddress);
    int getCenter();

private:
    std::vector<Client *> clients; // 客户端对象列表
};
#endif
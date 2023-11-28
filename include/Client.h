#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <vector>
#include "Protocol.h"

class Client
{
public:
    virtual void connectByIp(const std::string &ipAddress, int port) = 0;
    virtual void sendData(const std::string &data) = 0;
    virtual void sendLargeData(const char *largeData, int dataSize) = 0;
    virtual void receiveData(std::string &data) = 0;
    virtual void receiveLargeData(std::vector<char> &largeData, int dataSize) = 0;
    virtual void disconnect() = 0;

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
    void sendLargeData(const char *largeData, int dataSize) override;
    void receiveData(std::string &data) override;
    void receiveLargeData(std::vector<char> &largeData, int dataSize) override;
    void disconnect() override;
};

#endif
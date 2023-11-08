#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <vector>

class Client
{
public:
    virtual void connectByIp(const std::string &ipAddress, int port) = 0;
    virtual void sendData(const std::string &data) = 0;
    virtual void receiveData(std::string &data) = 0;
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
    void receiveData(std::string &data) override;
    void disconnect() override;
};

// 定义一个具体的UDPClient类，继承自抽象的Client类
class UDPClient : public Client
{
public:
    void connectByIp(const std::string &ipAddress, int port) override;
    void sendData(const std::string &data) override;
    void receiveData(std::string &data) override;
    void disconnect() override;
};

// 定义一个ClientManager类，用于管理Client对象
class ClientManager
{
private:
    std::vector<Client *> clients;

public:
    void addClient(Client *client);
    void removeClient(Client *client);
    void connectAll();
    void sendDataAll(const std::string &data);
    void receiveDataAll(std::vector<std::string> &receivedData);
    void disconnectAll();
};

#endif
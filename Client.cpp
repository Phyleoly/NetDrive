#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "Client.h"

void TCPClient::connectByIp(const std::string &ipAddress, int port)
{
    // 创建套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // 设置服务器的IP地址和端口号
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, ipAddress, &(serverAddress.sin_addr)) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return 1;
    }

    // 连接到服务器
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        return 1;
    }
}

void TCPClient::sendData(const std::string &data)
{
    if (send(clientSocket, message, strlen(data), 0) < 0)
    {
        std::cerr << "Send failed" << std::endl;
        return 1;
    }
}

void TCPClient::receiveData(std::string &data)
{
    if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0)
    {
        std::cerr << "Receive failed" << std::endl;
        return 1;
    }
}

void TCPClient::void disconnect()
{
    close(clientSocket);
}

void UDPClient::connectByIp(const std::string &ipAddress, int port)
{
    // 创建套接字
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }

    // 设置服务器的IP地址和端口号
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, ipAddress.c_str(), &(serverAddress.sin_addr)) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return;
    }

    // 连接到服务器（UDP不需要连接操作）

    // 将服务器地址保存起来
    serverAddr = serverAddress;
}

void UDPClient::sendData(const std::string &data)
{
    if (sendto(clientSocket, data.c_str(), data.length(), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Send failed" << std::endl;
        return;
    }
}

void UDPClient::receiveData(std::string &data)
{
    char buffer[MAX_BUFFER_SIZE];
    socklen_t serverAddrLen = sizeof(serverAddr);
    int bytesRead = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddr, &serverAddrLen);
    if (bytesRead < 0)
    {
        std::cerr << "Receive failed" << std::endl;
        return;
    }
    data = std::string(buffer, bytesRead);
}

void UDPClient::disconnect()
{
    close(clientSocket);
}

void ClientManager::addClient(Client *client)
{
    clients.push_back(client);
}

void ClientManager::removeClient(Client *client)
{
    for (auto it = clients.begin(); it != clients.end(); ++it)
    {
        if (*it == client)
        {
            clients.erase(it);
            break;
        }
    }
}

void ClientManager::connectAll()
{
    for (auto client : clients)
    {
        client->connect();
    }
}

void ClientManager::sendDataAll(const std::string &data)
{
    for (auto client : clients)
    {
        client->sendData(data);
    }
}

void ClientManager::receiveDataAll(std::vectorstd::string &receivedData)
{
    for (auto client : clients)
    {
        std::string data = client->receiveData();
        receivedData.push_back(data);
    }
}

void ClientManager::disconnectAll()
{
    for (auto client : clients)
    {
        client->disconnect();
    }
}
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "include/Server.h"

std::string Server::getipAddress()
{
    return this->ipAddress;
}

int Server::getport()
{
    return this->port;
}

void TCPServer::start()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        // return 1;
    }

    // 设置服务器的IP地址和端口号
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(getport());

    // 绑定套接字到指定的IP地址和端口号
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        // return 1;
    }

    // 监听连接请求
    if (listen(serverSocket, 3) < 0)
    {
        std::cerr << "Listen failed" << std::endl;
        // return 1;
    }

    std::cout << "Waiting for incoming connections..." << std::endl;

 
    // 接受连接请求
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);
    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength)) < 0)
    {
        std::cerr << "Accept failed" << std::endl;
        // return 1;
    }
    // std::cerr<<1;
}

// 发送数据
void TCPServer::sendData(const std::string& data)
{
    send(clientSocket, data.c_str(), data.size(), 0);
}

// 传输4M大小的文件块
void TCPServer::sendLargeData(const char* largeData, int dataSize)
{
    int bytesSent = 0;
    int totalBytesSent = 0;
    while (totalBytesSent < dataSize)
    {
        bytesSent = send(clientSocket, largeData + totalBytesSent, dataSize - totalBytesSent, 0);
        if (bytesSent == -1)
        {
            std::cerr << "Send failed" << std::endl;
            break;
        }
        totalBytesSent += bytesSent;
    }
}

// 接收数据
void TCPServer::receiveData(std::string &data)
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived < 0)
    {
        std::cerr << "Receive failed" << std::endl;
    }
    else
    {
        data = std::string(buffer, bytesReceived);
    }
}

// 接收4M大小的文件块
void TCPServer::receiveLargeData(char* largeData, int dataSize)
{
    int bytesReceived = 0;
    int totalBytesReceived = 0;
    while (totalBytesReceived < dataSize)
    {
        bytesReceived = recv(clientSocket, largeData + totalBytesReceived, dataSize - totalBytesReceived, 0);
        if (bytesReceived == -1)
        {
            std::cerr << "Receive failed" << std::endl;
            break;
        }
        totalBytesReceived += bytesReceived;
    }
}

void TCPServer::stop()
{

    // 关闭套接字
    close(serverSocket);
    close(clientSocket);
}

int main() 
{
    TCPServer test;
    test.start();
    return 0;
}
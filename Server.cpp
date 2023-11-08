#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "Server.h"

std::string Server::getipAddress();
{
    return this.ipAddress;
}

int Server::getport();
{
    return this.port;
}

void TCPServer::start()
{
    // serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // if (serverSocket == -1)
    // {
    //     std::cerr << "Failed to create socket" << std::endl;
    //     return 1;
    // }

    // // 设置服务器的IP地址和端口号
    // serverAddress.sin_family = AF_INET;
    // serverAddress.sin_addr.s_addr = INADDR_ANY;
    // serverAddress.sin_port = htons(getport());

    // // 绑定套接字到指定的IP地址和端口号
    // if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    // {
    //     std::cerr << "Bind failed" << std::endl;
    //     return 1;
    // }

    // // 监听连接请求
    // if (listen(serverSocket, 3) < 0)
    // {
    //     std::cerr << "Listen failed" << std::endl;
    //     return 1;
    // }

    // std::cout << "Waiting for incoming connections..." << std::endl;

    // // 接受连接请求
    // int clientSocket;
    // sockaddr_in clientAddress{};
    // socklen_t clientAddressLength = sizeof(clientAddress);
    // if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength)) < 0)
    // {
    //     std::cerr << "Accept failed" << std::endl;
    //     return 1;
    // }

    //   // 接收和发送数据
    // char buffer[1024];
    // memset(buffer, 0, sizeof(buffer));
    // if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
    //     std::cerr << "Receive failed" << std::endl;
    //     return 1;
    // }
    // std::cout << "Client message: " << buffer << std::endl;

    // char message[1024];
    // strcpy(message, "Hello from server");
    // if (send(clientSocket, message, strlen(message), 0) < 0) {
    //     std::cerr << "Send failed" << std::endl;
    //     return 1;
    // }

    // // 关闭套接字
    // close(serverSocket);
    // close(clientSocket);
}

void TCPServer::receiveData(const std::string &data)
{
}
 
 void TCPServer::sendData(const std::string &data) {

 }
 void TCPServer::stop() {

 }
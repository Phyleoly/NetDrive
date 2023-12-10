#include "include/Client.h"

// TCPClient::TCPClient()
// {
//     // 构造函数的实现
// }

// TCPClient::~TCPClient()
// {
//     // 构造函数的实现
// }

void TCPClient::connectByIp(const std::string &ipAddress, int port)
{
    // 创建套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        // return 1;
    }

    // 设置服务器的IP地址和端口号
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    const char *ipAddressChar = ipAddress.c_str();
    if (inet_pton(AF_INET, ipAddressChar, &(serverAddress.sin_addr)) <= 0)
    {
        std::cerr << std::endl
                  << ipAddressChar << std::endl
                  << "Invalid address/ Address not supported" << std::endl;
        return;
    }

    // 连接到服务器
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        return;
    }
}

// 发送自定义协议的数据
void TCPClient::sendData(const std::string &data)
{
    const char *buffer = data.c_str();
    if (send(clientSocket, buffer, strlen(buffer), 0) < 0)
    {
        std::cerr << "Send failed" << std::endl;
    }
}

// 发送4M大小的文件块
void TCPClient::sendLargeData(const char *largeData, int dataSize)
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

// 接收自定义协议的数据
void TCPClient::receiveData(std::string &data)
{
    const int bufferSize = 1024;             // 选择一个合适的缓冲区大小
    std::vector<char> buffer(bufferSize, 0); // 使用vector作为缓冲区

    int bytesReceived = recv(clientSocket, buffer.data(), bufferSize, 0);
    if (bytesReceived < 0)
    {
        std::cerr << "Receive failed" << std::endl;
    }
    else
    {
        data.assign(buffer.data(), bytesReceived); // 将接收到的数据存入std::string
    }
}

// 接收4M大小的文件块
void TCPClient::receiveLargeData(std::vector<char> &largeData, int dataSize)
{
    int totalBytesReceived = 0;
    while (totalBytesReceived < dataSize)
    {
        const int bufferSize = 1024;             // 选择一个合适的缓冲区大小
        std::vector<char> buffer(bufferSize, 0); // 使用vector作为缓冲区

        int bytesReceived = recv(clientSocket, buffer.data(), buffer.size(), 0);
        if (bytesReceived < 0)
        {
            std::cerr << "Receive failed" << std::endl;
            break;
        }
        totalBytesReceived += bytesReceived;
        largeData.insert(largeData.end(), buffer.begin(), buffer.begin() + bytesReceived);
    }
}

void TCPClient::disconnect()
{
    close(clientSocket);
}

// UDPClient::UDPClient()
// {
//     // 构造函数的实现
// }

// UDPClient::~UDPClient()
// {
//     // 构造函数的实现
// }

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
    const int bufferSize = 1024;
    char buffer[bufferSize];
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

void ClientManager::createClient(const std::string &clientType, const std::string &ipAddress, int port)
{
    Client *client = nullptr;
    if (clientType == "TCP")
    {
        client = new TCPClient();
    }
    else if (clientType == "UDP")
    {
        client = new UDPClient();
    }
    client->setIpAddress(ipAddress);
    client->setPort(port);
    clients.push_back(client);
}

void ClientManager::deleteClient(int index)
{
    if (index >= 0 && index < clients.size())
    {
        delete clients[index];
        clients.erase(clients.begin() + index);
    }
}

Client *ClientManager::getClient(int index)
{
    if (index >= 0 && index < clients.size())
    {
        return clients[index];
    }
    return nullptr;
}

void ClientManager::connectClient(int index)
{
    if (index >= 0 && index < clients.size())
    {
        clients[index]->connectByIp(clients[index]->getIpAddress(), clients[index]->getPort());
    }
}

void ClientManager::disconnectClient(int index)
{
    if (index >= 0 && index < clients.size())
    {
        clients[index]->disconnect();
    }
}

void ClientManager::sendData(int index, const std::string &data)
{
    if (index >= 0 && index < clients.size())
    {
        clients[index]->sendData(data);
    }
}

void ClientManager::sendLargeData(int index, const char *largeData, int dataSize)
{
    if (index >= 0 && index < clients.size())
    {
        clients[index]->sendLargeData(largeData, dataSize);
    }
}

void ClientManager::receiveData(int index, std::string &data)
{
    if (index >= 0 && index < clients.size())
    {
        clients[index]->receiveData(data);
    }
}

void ClientManager::receiveLargeData(int index, std::vector<char> &largeData, int dataSize)
{
    if (index >= 0 && index < clients.size())
    {
        clients[index]->receiveLargeData(largeData, dataSize);
    }
}

int ClientManager::getClientCount()
{
    return clients.size();
}

int ClientManager::findClientIndexByIp(const std::string &ipAddress)
{
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i]->getIpAddress() == ipAddress)
        {
            return i; // 返回找到的客户端索引
        }
    }
    return -1; // 如果未找到匹配的IP地址，返回-1
}

int ClientManager::getCenter() { return 0; }

void ClientManager::registerUDP(ThreadPool threadPool, Client *client)
{
    // threadPool.addTask([&client]()
    //                    { client.connectByIp("127.0.0.1", 8080);

    //                    });
}

#include "include/Command.h"

Command *CommandParser::parseCommand(const std::string &commandStr)
{
    Command *ret;
    std::istringstream iss(commandStr);
    std::string token;

    // 解析命令类型
    if (std::getline(iss, token, ' '))
    {
        std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c)
                       { return std::tolower(c); });
        // 根据commandStr解析出对应的Command对象
        // 这里只是一个简单的示例，实际情况可能会更复杂
        if (token == "exit")
            ret = new ExitCommand();
        else if (token == "sendblock")
            ret = new SendBlockCommand();
        // else if (token == "deleteblock")
        //     ret = new DeleteBlockCommand();
        else if (token == "mkdir")
            ret = new MkdirCommand();
        else if (token == "rmdir")
            ret = new RmdirCommand();
        // else if (token == "Delete")
        // {
        //     ret = std::make_unique<DeleteCommand>();
        // }
        else
        {
            // 如果无法解析出对应的Command对象，可以返回nullptr或者抛出异常
            ret = nullptr;
        }
    }

    // 解析参数
    while (std::getline(iss, token, ' '))
    {
        // 将解析出的参数存储到parameter中
        ret->pushParameter(token);
    }
    return ret;
}

std::string Protocol::generateProtocolString(Command *command)
{
    std::string protocolString;

    // 将命令对象的各个属性按照协议规则转换为字符串，并拼接到生成的协议字符串中
    protocolString += "CommandType: " + command->getCommandType() + "\n";
    std::cout << std::endl
              << command->getParameterNum() << std::endl;
    for (int i = 0; i < command->getParameterNum(); i++)
    {
        protocolString += "Parameter" + std::to_string(i) + ": " + command->getParameter(i) + "\n";
    }
    // ...

    return protocolString;
}

Command *Protocol::parseProtocolString(const std::string &protocolString)
{

    std::string input = protocolString;
    // 删除CommandType
    size_t pos = input.find("CommandType:");
    if (pos != std::string::npos)
    {
        input.erase(pos, 12); // 删除"CommandType:"
    }

    // 删除Parameter1
    pos = input.find("Parameter1:");
    if (pos != std::string::npos)
    {
        input.erase(pos, 11); // 删除"Parameter1:"
    }

    // 将换行符替换成空格
    while ((pos = input.find("\n")) != std::string::npos)
    {
        input.replace(pos, 1, " "); // 替换换行符为空格
    }

    CommandParser commandParser;
    return commandParser.parseCommand(input);
}

// 命令
std::string OKCommand::getCommandType() { return "OK"; }
void OKCommand::execute(CommandData *commandData) {}

std::string NoCommand::getCommandType() { return "NO"; }
void NoCommand::execute(CommandData *commandData) {}

std::string ExitCommand::getCommandType() { return "exit"; }
void ExitCommand::execute(CommandData *commandData) { exit(0); }

std::string MkdirCommand::getCommandType() { return "mkdir"; }
void MkdirCommand::execute(CommandData *commandData)
{
    Protocol protocol;
    if (commandData->ifServer)
    {
        FileSystem *fileSystem = commandData->fileSystem;
        fileSystem->createDirectory(this->getParameter(0));
        // 返回OK
        OKCommand ok;
        commandData->messageServer->sendData(protocol.generateProtocolString(&ok));
    }
    else
    {
        // commandData->messageClient->connectServer();
        commandData->messageClient->sendData(protocol.generateProtocolString(this));

        std::string messageData;
        commandData->messageClient->receiveData(messageData);
        Command *command = protocol.parseProtocolString(messageData);

        if (command->getCommandType() == "ok")
        {
            // OK处理
        }
        else
        {
            // ERROR处理
            std::cout << "ERROR";
        }
    }
}

std::string RmdirCommand::getCommandType() { return "rmdir"; }
void RmdirCommand::execute(CommandData *commandData)
{
    Protocol protocol;
    if (commandData->ifServer)
    {
        FileSystem *fileSystem = commandData->fileSystem;
        fileSystem->deleteDirectory(this->getParameter(0));
        // 返回OK
        OKCommand ok;
        commandData->messageServer->sendData(protocol.generateProtocolString(&ok));
    }
    else
    {
        // commandData->messageClient->connectServer();
        commandData->messageClient->sendData(protocol.generateProtocolString(this));

        std::string messageData;
        commandData->messageClient->receiveData(messageData);
        Command *command = protocol.parseProtocolString(messageData);

        if (command->getCommandType() == "ok")
        {
            // OK处理
        }
        else
        {
            // ERROR处理
            std::cout << "ERROR";
        }
    }
}

std::string UploadCommand::getCommandType() { return "upload"; }
void UploadCommand::execute(CommandData *commandData)
{
    if (commandData->ifServer)
    {
    }
    else
    {
        UDPClient UDPClient;
    }
}

std::string DownloadCommand::getCommandType() { return "download"; }
void DownloadCommand::execute(CommandData *commandData)
{
}

std::string SendBlockCommand::getCommandType() { return "sendblock"; }
void SendBlockCommand::execute(CommandData *commandData)
{
}

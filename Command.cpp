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
        else if(token == "mkdir")
            ret = new Mkdircommand();
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

void CommandExecutor::executeSCommand(Command *command, ServerManager serverManager) { command->executeS(serverManager); }

void CommandExecutor::executeCCommand(Command *command, ClientManager clientManager) { command->executeC(clientManager); }

std::string Protocol::generateProtocolString(Command* command)
{
    std::string protocolString;

    // 将命令对象的各个属性按照协议规则转换为字符串，并拼接到生成的协议字符串中
    protocolString += "CommandType: " + command->getCommandType() + "\n";
    std::cout<<std::endl<<command->getParameterNum()<<std::endl;
    for (int i = 0; i < command->getParameterNum(); i++)
    {
        protocolString += "Parameter" + std::to_string(i) + ": " + command->getParameter(i) + "\n";
    }
    // ...

    return protocolString;
}

Command* Protocol::parseProtocolString(const std::string &protocolString)
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
std::string ExitCommand::getCommandType() { return "exit"; }
void ExitCommand::executeC(ClientManager clientManager) { exit(0); }
void ExitCommand::executeS(ServerManager serverManager) { exit(0); }

std::string Mkdircommand::getCommandType() {return "mkdir";}

void Mkdircommand::executeC(ClientManager clientManager) 
{
    Protocol protocol;
    std::string request;
    request = protocol.generateProtocolString(this);
    clientManager.sendData(clientManager.getCenter(), request);
}
void Mkdircommand::executeS(ServerManager servermanager)
{

}
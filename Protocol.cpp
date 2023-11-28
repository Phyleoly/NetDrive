#include "include/Protocol.h"

std::string Protocol::generateProtocolString(Command &command)
{
    std::string protocolString;

    // 将命令对象的各个属性按照协议规则转换为字符串，并拼接到生成的协议字符串中
    protocolString += "CommandType: " + command.getCommandType() + "\n";
    for (int i = 1; i <= command.getParameterNum(); i++)
    {
        protocolString += "Parameter" + std::to_string(i) + ": " + command.getParameter(i) + "\n";
    }
    // ...

    return protocolString;
}

std::unique_ptr<Command> Protocol::parseProtocolString(const std::string &protocolString)
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
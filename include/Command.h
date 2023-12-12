#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include "File.h"
#include "Client.h"
#include "Server.h"

class CommandData
{
public:
    FileSystem *fileSystem = nullptr;
    std::string ipAddress;
    int port;
    bool ifServer; // 0 Client  1 Server

    UDPServer* messageServer = nullptr;
    UDPClient* messageClient = nullptr;
};

// 命令类
class Command
{
public:
    virtual void execute(CommandData *commandData) = 0;
    virtual std::string getCommandType() = 0;
    std::string getParameter(int i) { return parameter.at(i); }
    int getParameterNum() { return parameter.size(); }
    void pushParameter(std::string params) { parameter.push_back(params); }

private:
    std::vector<std::string> parameter;
};

class OKCommand : public Command
{
public:
    std::string getCommandType() override;
    void execute(CommandData *commandData) override;
};

class NoCommand : public Command
{
public:
    std::string getCommandType() override;
    void execute(CommandData *commandData) override;
};

class ExitCommand : public Command
{
public:
    std::string getCommandType() override;
    void execute(CommandData *commandData) override;
};

class SendBlockCommand : public Command
{
    std::string getCommandType() override;
    void execute(CommandData *commandData) override;
};

// class DeleteBlockCommand : public Command
// {
//     std::string getCommandType() override;
//     void execute(CommandData* commandData) override;
// };

// 创建文件夹命令类
class MkdirCommand : public Command
{
public:
    std::string getCommandType() override;
    // CreateFolderCommand(const std::string &folderName, const std::string &parentPath);
    void execute(CommandData *commandData) override;
};

// 删除文件夹命令类
class RmdirCommand : public Command
{
public:
    std::string getCommandType() override;
    // DeleteCommand(const std::string &path);
    void execute(CommandData *commandData) override;
};

// 分享文件或文件夹命令类
class UploadCommand : public Command
{
public:
    std::string getCommandType() override;
    // DeleteCommand(const std::string &path);
    void execute(CommandData *commandData) override;
};

//
class DownloadCommand : public Command
{
public:
    std::string getCommandType() override;
    // DeleteCommand(const std::string &path);
    void execute(CommandData *commandData) override;
};
// // 查看文件或文件夹列表命令类
// class ListCommand : public Command
// {
// public:
//     ListCommand(const std::string &path);
//     void execute() override;
// };

// // 查看文件或文件夹详情命令类
// class InfoCommand : public Command
// {
// public:
//     InfoCommand(const std::string &path);
//     void execute() override;
// };

// // 复制文件或文件夹命令类
// class CopyCommand : public Command
// {
// public:
//     CopyCommand(const std::string &sourcePath, const std::string &destinationPath);
//     void execute() override;
// };

// // 移动文件或文件夹命令类
// class MoveCommand : public Command
// {
// public:
//     MoveCommand(const std::string &sourcePath, const std::string &destinationPath);
//     void execute() override;
// };

// // 重命名文件或文件夹命令类
// class RenameCommand : public Command
// {
// public:
//     RenameCommand(const std::string &oldName, const std::string &newName);
//     void execute() override;
// };



// // 取消分享文件或文件夹命令类
// class UnshareCommand : public Command
// {
// public:
//     UnshareCommand(const std::string &path);
//     void execute() override;
// };

// // 查找文件或文件夹命令类
// class SearchCommand : public Command
// {
// public:
//     SearchCommand(const std::string &keyword);
//     void execute() override;
// };

// // 设置文件或文件夹权限命令类
// class SetPermissionsCommand : public Command
// {
// public:
//     SetPermissionsCommand(const std::string &path, const std::string &permissions);
//     void execute() override;
// };

// // 查看使用空间命令类
// class UsageCommand : public Command
// {
// public:
//     void execute() override;
// };

// // 查看版本信息命令类
// class VersionCommand : public Command
// {
// public:
//     void execute() override;
// };

// // 退出登录命令类
// class LogoutCommand : public Command
// {
// public:
//     void execute() override;
// };

// ... 其他命令类的定义

// 命令行解析器接口
class CommandParser
{
public:
    ~CommandParser() {}

    /**
     * 解析命令行字符串，根据命令类型返回相应的命令对象
     * @param commandStr 命令行字符串
     * @return 解析得到的命令对象
     */
    Command *parseCommand(const std::string &commandStr);
};

// 协议类
class Protocol
{
public:
    ~Protocol() {}

    /**
     * 根据命令对象生成协议字符串
     * @param command 命令对象
     * @return 生成的协议字符串
     */
    std::string generateProtocolString(Command *command);

    /**
     * 解析协议字符串，生成相应的命令对象
     * @param protocolString 协议字符串
     * @return 解析得到的命令对象
     */
    Command *parseProtocolString(const std::string &protocolString);

    /**
     * 验证协议字符串是否合法
     * @param protocolString 协议字符串
     * @return 验证结果，true表示合法，false表示不合法
     */
    bool validateProtocolString(const std::string &protocolString);

    /**
     * 处理协议字符串解析错误
     * @param error 错误信息
     */
    void handleParseError(const std::string &error);
};

#endif // COMMAND_H

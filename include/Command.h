#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <memory>

// 命令类
class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

// 创建文件夹命令类
class CreateFolderCommand : public Command
{
public:
    CreateFolderCommand(const std::string &folderName, const std::string &parentPath);
    void execute() override;
};

// 删除文件或文件夹命令类
class DeleteCommand : public Command
{
public:
    DeleteCommand(const std::string &path);
    void execute() override;
};

// 查看文件或文件夹列表命令类
class ListCommand : public Command
{
public:
    ListCommand(const std::string &path);
    void execute() override;
};

// 查看文件或文件夹详情命令类
class InfoCommand : public Command
{
public:
    InfoCommand(const std::string &path);
    void execute() override;
};

// 复制文件或文件夹命令类
class CopyCommand : public Command
{
public:
    CopyCommand(const std::string &sourcePath, const std::string &destinationPath);
    void execute() override;
};

// 移动文件或文件夹命令类
class MoveCommand : public Command
{
public:
    MoveCommand(const std::string &sourcePath, const std::string &destinationPath);
    void execute() override;
};

// 重命名文件或文件夹命令类
class RenameCommand : public Command
{
public:
    RenameCommand(const std::string &oldName, const std::string &newName);
    void execute() override;
};

// 分享文件或文件夹命令类
class ShareCommand : public Command
{
public:
    ShareCommand(const std::string &path);
    void execute() override;
};

// 取消分享文件或文件夹命令类
class UnshareCommand : public Command
{
public:
    UnshareCommand(const std::string &path);
    void execute() override;
};

// 查找文件或文件夹命令类
class SearchCommand : public Command
{
public:
    SearchCommand(const std::string &keyword);
    void execute() override;
};

// 设置文件或文件夹权限命令类
class SetPermissionsCommand : public Command
{
public:
    SetPermissionsCommand(const std::string &path, const std::string &permissions);
    void execute() override;
};

// 查看使用空间命令类
class UsageCommand : public Command
{
public:
    void execute() override;
};

// 查看版本信息命令类
class VersionCommand : public Command
{
public:
    void execute() override;
};

// 退出登录命令类
class LogoutCommand : public Command
{
public:
    void execute() override;
};

// ... 其他命令类的定义

// 命令行解析器接口
class CommandParser
{
public:
    virtual ~CommandParser() {}

    /**
     * 解析命令行字符串，根据命令类型返回相应的命令对象
     * @param commandStr 命令行字符串
     * @return 解析得到的命令对象
     */
    virtual std::unique_ptr<Command> parseCommand(const std::string &commandStr) = 0;
};

// 命令执行器接口
class CommandExecutor
{
public:
    virtual ~CommandExecutor() {}

    /**
     * 执行命令对象的execute()方法
     * @param command 命令对象
     */
    virtual void executeCommand(std::unique_ptr<Command> command) = 0;
};

/**
 * 命令行处理器接口函数
 * @param parser 命令行解析器对象
 * @param executor 命令执行器对象
 * @param commandStr 命令行字符串
 */
void processCommandLine(CommandParser &parser, CommandExecutor &executor, const std::string &commandStr)
{
    // 解析命令行字符串，得到相应的命令对象
    std::unique_ptr<Command> command = parser.parseCommand(commandStr);

    // 执行命令对象的execute()方法
    executor.executeCommand(std::move(command));
}

#endif // COMMAND_H


#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <iostream>
#include <memory>
#include "Command.h"

// 协议类
class Protocol
{
public:
virtual ~Protocol() {}

/**
 * 根据命令对象生成协议字符串
 * @param command 命令对象
 * @return 生成的协议字符串
 */
virtual std::string generateProtocolString(const Command &command);

/**
 * 解析协议字符串，生成相应的命令对象
 * @param protocolString 协议字符串
 * @return 解析得到的命令对象
 */
virtual std::unique_ptr<Command> parseProtocolString(const std::string &protocolString);

/**
 * 验证协议字符串是否合法
 * @param protocolString 协议字符串
 * @return 验证结果，true表示合法，false表示不合法
 */
virtual bool validateProtocolString(const std::string &protocolString);

/**
 * 处理协议字符串解析错误
 * @param error 错误信息
 */
virtual void handleParseError(const std::string &error);
};

#endif //PROTOCOL_H
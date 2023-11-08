#ifndef ID_HANDLER_H
#define ID_HANDLER_H

#include <string>
#include <unordered_set>

// 文件类型枚举
enum class FileType {
    File,
    Directory,
    FileBlock
};

// 文件系统ID处理类
class FileSystemIDHandler {
public:
    // 构造函数
    FileSystemIDHandler();

    // 生成一个新的ID
    std::string generateID();

    // 检查ID是否有效
    bool isValidID(const std::string& id);

    // 解析ID的类型
    FileType parseIDType(const std::string& id);

private:
    std::unordered_set<std::string> usedIDs; // 已使用的ID集合

    // 生成随机ID
    std::string generateRandomID();
};

#endif // ID_HANDLER_H

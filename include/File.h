#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include "Server.h"

class FileChunk {
public:
    FileChunk(const std::string& filePath, long long offset, int size, int id);
    ~FileChunk();

    std::vector<char>& getData(); // 获取块的数据向量的引用
    bool save(const std::string& filePath); // 将块保存到指定的文件路径
    int getId() const; // 获取块的ID
private:
    std::vector<char> data; // 块的数据向量
    std::string blockId; // 文件块ID
    std::string serverId; // 数据服务器ID
    std::string filePath; // 文件路径
    int blockSize; // 文件块大小
    int id; // 块的ID
};

// 定义备份器类
class Backup {
public:
    // 构造函数
    Backup();

    // 析构函数
    ~Backup();

    // 添加文件块到备份列表
    void addFileBlock(const FileChunk& fileBlock);

    // 备份文件块
    void backupFileBlocks();

private:
    // 数据服务器列表
    std::vector<Server> dataServers;

    // 备份列表
    std::vector<FileChunk> fileBlocks;

    // 获取备份的数据服务器列表
    std::vector<Server> getBackupDataServers();

    // 备份文件块到指定服务器
    void backupFileBlock(const FileChunk& fileBlock, const Server& dataServer);
};
    

class FileMetadata {
public:
    FileMetadata(const std::string& fileId);
    ~FileMetadata();

    std::string getFileId() const; // 获取文件的唯一标识符ID

    // Getter 和 Setter 方法用于访问和更新元数据属性
    std::string getFileName() const;
    void setFileName(const std::string& fileName);

    std::string getFileType() const;
    void setFileType(const std::string& fileType);

    std::string getFileSize() const;
    void setFileSize(const std::string& fileSize);

    std::string getCreationDate() const;
    void setCreationDate(const std::string& creationDate);

    std::string getModifiedData() const;
    void setModifiedDate(const std::string& modifiedDate);

    // 添加其他常见的元数据属性和相应的访问和更新方法

private:
    std::string fileId; // 文件的唯一标识符ID
    std::string fileName; // 文件名
    std::string fileType; // 文件类型
    std::string fileSize; // 文件大小
    std::string creationDate; // 创建日期
    std::string modifiedDate; // 修改日期
    std::string filePath; // 文件路径

    // 其他常见的元数据属性
};


class File {
public:
    File(const std::string& filePath, const std::string& outputDir, int blockSize = 4 * 1024 * 1024, int firstChunkId = 0);
    ~File();

    bool splitFile(); // 将文件分割成块
    bool mergeFiles(const std::string& outputFilePath, const std::string& fileName); // 将块合并成文件
    bool uploadChunk(FileChunk* chunk); // 上传文件块到存储空间
    void splitAndUploadFile(); // 拆分并上传文件
    bool mergeChunksAndDownload(const std::string& outputFilePath, const std::string& fileName); // 合并文件块并下载文件
private:
    std::string outputDir; // 输出目录
    int blockSize; // 块大小
    int firstChunkId; // 第一个块的ID
    std::vector<FileChunk*> chunks; // 块的集合
};

#endif

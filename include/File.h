#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <iostream>
#define MAX_BLOCK_SIZE 4194304
#define MAX_FILES_NUM 1024
#define MAX_SUBDIRECTORIES_NUM 1024

// #include "Server.h"
// #include "Client.h"

// 虚拟文件块类
// class Block
// {
// public:
//     Block(mp_pool_s *memoryPool);
//     ~Block();

//     void saveBlock();   // 将块保存到指定的实体文件路径
//     void removeBlock(); // 将块从实体文件删除
//     // void backup(Client *client);            // 将块备份到远程
//     // void removeBakeup(Client *client);      // 将块从远程移除

//     int *getId();
//     char *getData(); // 获取块的数据向量的引用
//     std::string *getFilePath();

// private:
//     int *id;
//     // Block* sameOrigin;           // 同源文件块id集合，即备份
//     char *data;            // 块的数据向量
//     std::string *filePath; // 块保存的实体路径
// };

class Block
{
public:
    Block();
    ~Block();

    void saveBlock();   // 将块保存到指定的实体文件路径
    void removeBlock(); // 将块从实体文件删除
    // void backup(Client *client);            // 将块备份到远程
    // void removeBakeup(Client *client);      // 将块从远程移除
    int getId();
    char *getData(); // 获取块的数据向量的引用
    int getDataSize();
    std::string getFilePath();

    template <typename T, typename... Args>
    void set(T arg, Args... args)
    {
        set(std::forward<T>(arg));
        set(std::forward<Args>(args)...);
    }
    template <typename T>
    void set(T arg);

private:
    unsigned int id;
    // Block* sameOrigin;           // 同源文件块id集合，即备份
    char *data;           // 块的数据向量
    std::string filePath; // 块保存的实体路径

    void setId(unsigned int id);
    void setData(char *data);
    void setFilePath(std::string filePath);
};

// 虚拟文件类
class File
{
public:
    // File(int id, std::string filePath, std::string outDir);
    ~File();
    unsigned int getId();
    std::string getFilePath();
    Block *getFirstBlock();
    unsigned int *getBlockId();

    std::string getName();
    std::string getOutDir();
    int getNumBlocks();

    void setOutDir(std::string outDir);
    void setNumBlocks(int num);
    void splitFile();
    void mergeFile();

    template <typename T, typename... Args>
    void set(T arg, Args... args)
    {
        set(std::forward<T>(arg));
        set(std::forward<Args>(args)...);
    }

    template <typename T>
    void set(T arg);

private:
    void setId(unsigned int id);
    void setBlockId(unsigned int *BlockId);
    void setFilePath(std::string filePath);
    void setBlocks(Block *blocks);

    unsigned int id;
    unsigned int *BlockId;
    int numBlocks;
    std::string filePath; // 文件保存的实体路径
    std::string outDir;   // 默认为当前路径
    Block *blocks;        // 对应的文件块集合
};

class Directory
{

public:
    // 设置目录下的文件列表
    //  Directory(int id, std::string directoryPath);
    unsigned int getId();
    std::string getName();
    std::string getDirectoryPath();
    int getNumFiles();
    int getNumSubdirectories();
    File **getFiles();
    Directory **getSubdirectories();

    template <typename T, typename... Args>
    void set(T arg, Args... args)
    {
        set(std::forward<T>(arg));
        set(std::forward<Args>(args)...);
    }
    template <typename T>
    void set(T arg);

   
    void setNumFiles(int numFile);
    void setNumSubdirectories(int numSubdirectories);

    // void setFiles(File *files[]);
    // void setSubdirectories(Directory *subdirectories[]);

    void initial();

    void addFile(File *file);
    void deleteFile(File *file);
    void addSubdirectory(Directory *directory);
    void deleteSubdirectory(Directory *directory);

    File *findFileByName(std::string fileName);
    File *findFileByPath(std::string path);
    Directory *findSubdirectoryByName(std::string directoryName);
    Directory *findSubdirectoryByPath(std::string path);

private:
    unsigned int id;
    std::string directoryPath;
    int numFiles = 0;
    int numSubdirectories = 0;
    File *files[MAX_FILES_NUM];
    Directory *subdirectories[MAX_SUBDIRECTORIES_NUM];
    // 目录属性和操作

    void setId(unsigned int id);
    void setDirectoryPath(std::string directoryPath);
};


// class PathS
// {
// public:
//     PathS(const std::string &path);

//     // std::string string();
//     // std::string filename();
//     // std::string extension();
//     // std::string parent_path();

//     // bool isAbsolute();
//     // bool isRelative();
//     // bool exists();
//     // bool isDirectory();
//     // bool isRegularFile();

//     // static PathS current_path();
//     // static PathS temp_directory_path();

//     // static bool create_directory(const std::string &path);
//     // static bool remove(const std::string &path);

//     // static bool copy(const std::string &source, const std::string &destination);
//     // static bool rename(const std::string &old_path, const std::string &new_path);
//     // static bool is_empty(const std::string &path);
//     // static bool remove_all(const std::string &path);
//     // static bool create_directories(const std::string &path);
//     // static bool create_hard_link(const std::string &existing_path, const std::string &new_path);
//     // static bool create_symlink(const std::string &existing_path, const std::string &new_path);

// private:
//     std::string m_path;
// };

// // // 定义备份器类
// // class Backup
// // {
// // public:
// //     Backup();
// //     ~Backup();

// //     // 添加文件块到备份列表
// //     void addFileBlock(const FileChunk &fileBlock);

// //     // 备份文件块
// //     void backupFileBlocks();

// // private:
// //     // 数据服务器列表
// //     std::vector<Server> dataServers;

// //     // 备份列表
// //     std::vector<FileChunk> fileBlocks;

// //     // 获取备份的数据服务器列表
// //     std::vector<Server> getBackupDataServers();

// //     // 备份文件块到指定服务器
// //     void backupFileBlock(const FileChunk &fileBlock, const Server &dataServer);
// // };

// // class FileMetadata
// // {
// // public:
// //     FileMetadata(const std::string &fileId);
// //     ~FileMetadata();

// //     std::string getFileId() const; // 获取文件的唯一标识符ID

// //     // Getter 和 Setter 方法用于访问和更新元数据属性
// //     std::string getFileName() const;
// //     void setFileName(const std::string &fileName);

// //     std::string getFileType() const;
// //     void setFileType(const std::string &fileType);

// //     std::string getFileSize() const;
// //     void setFileSize(const std::string &fileSize);

// //     std::string getCreationDate() const;
// //     void setCreationDate(const std::string &creationDate);

// //     std::string getModifiedData() const;
// //     void setModifiedDate(const std::string &modifiedDate);

// //     // 添加其他常见的元数据属性和相应的访问和更新方法

// // private:
// //     std::string fileId;       // 文件的唯一标识符ID
// //     std::string fileName;     // 文件名
// //     std::string fileType;     // 文件类型
// //     std::string fileSize;     // 文件大小
// //     std::string creationDate; // 创建日期
// //     std::string modifiedDate; // 修改日期
// //     std::string filePath;     // 文件路径

// //     // 其他常见的元数据属性
// // };

// // class File
// // {
// // public:
// //     File(const std::string &filePath, const std::string &outputDir, int blockSize = 4 * 1024 * 1024, int firstChunkId = 0);
// //     ~File();

// //     bool splitFile();                                                                            // 将文件分割成块
// //     bool mergeFiles(const std::string &outputFilePath, const std::string &fileName);             // 将块合并成文件
// //     bool uploadChunk(FileChunk *chunk);                                                          // 上传文件块到存储空间
// //     void splitAndUploadFile();                                                                   // 拆分并上传文件
// //     bool mergeChunksAndDownload(const std::string &outputFilePath, const std::string &fileName); // 合并文件块并下载文件
// // private:
// //     std::string outputDir;           // 输出目录
// //     std::string cacheDir;            // 缓存目录
// //     int blockSize;                   // 块大小
// //     std::vector<FileChunk *> chunks; // 块的集合
// // };

#endif
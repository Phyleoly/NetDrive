#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <iostream>
// #include "mmPool.h"
#define MAX_BLOCK_SIZE 4194304
#define MAX_FILES_NUM 1024
#define MAX_SUBDIRECTORIES_NUM 1024

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

    // template <typename T, typename... Args>
    // void set(T arg, Args... args)
    // {
    //     set(std::forward<T>(arg));
    //     set(std::forward<Args>(args)...);
    // }
    // template <typename T>
    // void set(T arg);


    void setId(unsigned int id);
    void setData(char *data);
    void setFilePath(std::string filePath);
private:
    unsigned int id;
    // Block* sameOrigin;           // 同源文件块id集合，即备份
    char *data;           // 块的数据向量
    std::string filePath; // 块保存的实体路径
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


    
    void setId(unsigned int id);
    void setBlockId(unsigned int *BlockId);
    void setFilePath(std::string filePath);
    void setBlocks(Block *blocks);
    // template <typename T, typename... Args>
    // void set(T arg, Args... args)
    // {
    //     set(std::forward<T>(arg));
    //     set(std::forward<Args>(args)...);
    // }

    // template <typename T>
    // void set(T arg);

private:

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

    // template <typename T, typename... Args>
    // void set(T arg, Args... args)
    // {
    //     set(std::forward<T>(arg));
    //     set(std::forward<Args>(args)...);
    // }
    // template <typename T>
    // void set(T arg);

   
    void setNumFiles(int numFile);
    void setNumSubdirectories(int numSubdirectories);

    
    void setId(unsigned int id);
    void setDirectoryPath(std::string directoryPath);

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

};



class FileSystem
{
public:
    // FileSystem();
    // ~FileSystem();

    void initialize(); // 初始化文件系统
    Directory *findDirectoryByPathRoot(std::string directoryPath);
    void createDirectory(std::string directoryPath);
    void deleteDirectory(std::string directoryPath); // 创建目录

    File *findFileByPathRoot(std::string filePath);
    void createFile(std::string filePath); // 创建文件
    void deleteFile(std::string filePath);

    // 删除文件                       // 删除目录
    // void moveFile(std::string sourcePath, std::string destinationPath);      // 移动文件
    // void moveDirectory(std::string sourcePath, std::string destinationPath); // 移动目录
    // void copyFile(std::string sourcePath, std::string destinationPath);      // 复制文件
    // void copyDirectory(std::string sourcePath, std::string destinationPath); // 复制目录
    // void listFiles(std::string directoryPath);                               // 列出目录下的文件
    // void listDirectories(std::string directoryPath);                         // 列出目录下的子目录
    // void searchFile(std::string fileName);                                   // 搜索文件
    // void searchDirectory(std::string directoryName);                         // 搜索目录
    // private:
    unsigned int newDirectoryId;
    unsigned int newFileId;
    Directory *rootDirectory;    // 根目录
    Directory *currentDirectory; // 当前目录

    void setCurrentDirectory(Directory *directory); // 设置当前目录
    // Directory *findDirectoryByPath(std::string path); // 根据路径查找目录
    // File *findFileByPath(std::string path);           // 根据路径查找文件
    // std::string getAbsolutePath(std::string path);    // 获取绝对路径
};



// void FileSystem::moveFile(std::string sourcePath, std::string destinationPath)
// {
//     File *file = currentDirectory->findFileByPath(sourcePath);
//     if (file != nullptr)
//     {
//         currentDirectory->deleteFile(file);
//         file->set(destinationPath);
//         currentDirectory->addFile(file);
//     }
//     else
//     {
//         std::cout << "File not found." << std::endl;
//     }
// }

// void FileSystem::moveDirectory(std::string sourcePath, std::string destinationPath)
// {
//     Directory *directory = currentDirectory->findSubdirectoryByPath(sourcePath);
//     if (directory != nullptr)
//     {
//         currentDirectory->deleteSubdirectory(directory);
//         directory->set(destinationPath);
//         currentDirectory->addSubdirectory(directory);
//     }
//     else
//     {
//         std::cout << "Directory not found." << std::endl;
//     }
// }

// void FileSystem::copyFile(std::string sourcePath, std::string destinationPath)
// {
//     File *sourceFile = currentDirectory->findFileByPath(sourcePath);
//     if (sourceFile != nullptr)
//     {
//         File *destinationFile = new File();
//         destinationFile->set(destinationPath);
//         // destinationFile->setBlocks(sourceFile->getFirstBlock(), sourceFile->getNumBlocks());
//         currentDirectory->addFile(destinationFile);
//     }
//     else
//     {
//         std::cout << "File not found." << std::endl;
//     }
// }

// void FileSystem::copyDirectory(std::string sourcePath, std::string destinationPath)
// {
//     Directory *sourceDirectory = currentDirectory->findSubdirectoryByPath(sourcePath);
//     if (sourceDirectory != nullptr)
//     {
//         Directory *destinationDirectory = new Directory();
//         destinationDirectory->set(destinationPath);
//         destinationDirectory->setNumFiles(sourceDirectory->getNumFiles());
//         destinationDirectory->setNumSubdirectories(sourceDirectory->getNumSubdirectories());

//         for (int i = 0; i < sourceDirectory->getNumFiles(); i++)
//         {
//             File *sourceFile = sourceDirectory->getFiles()[i];
//             File *destinationFile = new File();
//             destinationFile->set(destinationPath + "/" + sourceFile->getName());
//             // destinationFile->setBlocks(sourceFile->getFirstBlock(), sourceFile->getNumBlocks());
//             destinationDirectory->addFile(destinationFile);
//         }

//         for (int i = 0; i < sourceDirectory->getNumSubdirectories(); i++)
//         {
//             Directory *sourceSubdirectory = sourceDirectory->getSubdirectories()[i];
//             Directory *destinationSubdirectory = new Directory();
//             destinationSubdirectory->set(destinationPath + "/" + sourceSubdirectory->getName());
//             destinationSubdirectory->setNumFiles(sourceSubdirectory->getNumFiles());
//             destinationSubdirectory->setNumSubdirectories(sourceSubdirectory->getNumSubdirectories());
//             destinationDirectory->addSubdirectory(destinationSubdirectory);
//         }

//         currentDirectory->addSubdirectory(destinationDirectory);
//     }
//     else
//     {
//         std::cout << "Directory not found." << std::endl;
//     }
// }

// void FileSystem::listFiles(std::string directoryPath)
// {
//     Directory *directory = currentDirectory->findSubdirectoryByPath(directoryPath);
//     if (directory != nullptr)
//     {
//         std::cout << "Files in " << directoryPath << ":" << std::endl;
//         for (int i = 0; i < directory->getNumFiles(); i++)
//         {
//             std::cout << directory->getFiles()[i]->getName() << std::endl;
//         }
//     }
//     else
//     {
//         std::cout << "Directory not found." << std::endl;
//     }
// }

// void FileSystem::listDirectories(std::string directoryPath)
// {
//     Directory *directory = currentDirectory->findSubdirectoryByPath(directoryPath);
//     if (directory != nullptr)
//     {
//         std::cout << "Subdirectories in " << directoryPath << ":" << std::endl;
//         for (int i = 0; i < directory->getNumSubdirectories(); i++)
//         {
//             std::cout << directory->getSubdirectories()[i]->getName() << std::endl;
//         }
//     }
//     else
//     {
//         std::cout << "Directory not found." << std::endl;
//     }
// }

// void FileSystem::searchFile(std::string fileName)
// {
//     File *file = currentDirectory->findFileByName(fileName);
//     if (file != nullptr)
//     {
//         std::cout << "File found: " << file->getFilePath() << std::endl;
//     }
//     else
//     {
//         std::cout << "File not found." << std::endl;
//     }
// }

// void FileSystem::searchDirectory(std::string directoryName)
// {
//     Directory *directory = currentDirectory->findSubdirectoryByName(directoryName);
//     if (directory != nullptr)
//     {
//         std::cout << "Directory found: " << directory->getName() << std::endl;
//     }
//     else
//     {
//         std::cout << "Directory not found." << std::endl;
//     }
// }





#endif
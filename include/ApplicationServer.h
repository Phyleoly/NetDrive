#ifndef APPLICATIONSERVER_H
#define APPLICATIONSERVER_H



#include <iostream>

struct mp_pool_s *memoryPool = mp_create_pool(123123);

template <typename T>
void Block::set(T arg) { std::cerr << " no patch " << std::endl; }
template <>
void Block::set<unsigned int>(unsigned int id) { setId(id); }
template <>
void Block::set<std::string>(std::string filePath) { setFilePath(filePath); }
template <>
void Block::set<char *>(char *data) { setData(data); }

template <typename T>
void File::set(T arg) { std::cerr << " no patch " << std::endl; }
template <>
void File::set<unsigned int>(unsigned int id) { setId(id); }
template <>
void File::set<std::string>(std::string filePath) { setFilePath(filePath); }
template <>
void File::set<const char *>(const char *filePath)
{
    std::string path(filePath);
    setFilePath(path);
}
template <>
void File::set<Block *>(Block *blocks) { setBlocks(blocks); }

template <typename T>
void Directory::set(T arg) { std::cerr << " no patch " << std::endl; }
template <>
void Directory::set<unsigned int>(unsigned int id) { setId(id); }
template <>
void Directory::set<std::string>(std::string directoryPath) { setDirectoryPath(directoryPath); }

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

void FileSystem::initialize()
{
    this->newDirectoryId = 0;
    this->newFileId = 0;

    std::string path("");

    this->rootDirectory = (Directory *)mp_alloc(memoryPool, sizeof(Directory));
    this->rootDirectory->set(this->newDirectoryId);

    // Directory* test = (Directory *)mp_alloc(memoryPool, sizeof(Directory));;
    // this->rootDirectory->addSubdirectory(test);

    this->currentDirectory = rootDirectory;
}

Directory *FileSystem::findDirectoryByPathRoot(std::string directoryPath)
{
    if (directoryPath == "")
        return rootDirectory;
    Directory *current = rootDirectory; // 从根目录开始
    Directory *subDirectory = nullptr;
    std::string token;
    size_t pos = 0;
    directoryPath.erase(0, 1); // 从路径中删除已处理的目录名
    while (!directoryPath.empty() && (pos = directoryPath.find_first_of("/")) != std::string::npos)
    {
        token = directoryPath.substr(0, pos);

        current = current->findSubdirectoryByName(token);
        if (current == nullptr)
            return nullptr;
        directoryPath.erase(0, pos + 1); // 从路径中删除已处理的目录名
        std::cout << directoryPath << std::endl
                  << token << std::endl;
    }

    return current->findSubdirectoryByName(directoryPath);
}

void FileSystem::createDirectory(std::string directoryPath)
{
    // 检查directoryPath是否为空
    if (directoryPath.empty())
    {
        std::cout << "Invalid directory path." << std::endl;
        return;
    }
    // 检查directoryPath是否以/开头
    if (directoryPath[0] != '/')
    {
        std::cout << "Invalid directory path. Path must start with /." << std::endl;
        return;
    }
    int pos = directoryPath.find_last_of('/');
    std::string dirFatherPath = directoryPath.substr(0, pos);
    Directory *dirFather = findDirectoryByPathRoot(dirFatherPath);
    if (dirFather == nullptr)
    {
        // std::cout<<"not found"<<std::endl;
        return;
    }
    Directory *directory = (Directory *)mp_alloc(memoryPool, sizeof(Directory));
    directory->set(directoryPath);
    dirFather->addSubdirectory(directory);
}

void FileSystem::deleteDirectory(std::string directoryPath)
{
    Directory *directory = findDirectoryByPathRoot(directoryPath);
    if (directory != nullptr)
    {
        currentDirectory->deleteSubdirectory(directory);
        delete directory;
    }
    else
    {
        std::cout << "Directory not found." << std::endl;
    }
}

File *FileSystem::findFileByPathRoot(std::string filePath)
{
    int pos = filePath.find_last_of("/");
    std::string dirPath = filePath.substr(0, pos);
    std::string fileName = filePath.substr(pos + 1);
    Directory *diretory = findDirectoryByPathRoot(dirPath);
    return diretory->findFileByName(fileName);
}

void FileSystem::createFile(std::string filePath)
{
    int pos = filePath.find_last_of("/");
    std::string dirPath = filePath.substr(0, pos);
    Directory *diretory = findDirectoryByPathRoot(dirPath);
    File *file = (File *)mp_alloc(memoryPool, sizeof(File));
    file->set(filePath);
    diretory->addFile(file);
}

void FileSystem::deleteFile(std::string filePath)
{
    File *file = findFileByPathRoot(filePath);
    if (file != nullptr)
    {
        currentDirectory->deleteFile(file);
        delete file;
    }
    else
    {
        std::cout << "File not found." << std::endl;
    }
}

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

void FileSystem::setCurrentDirectory(Directory *directory)
{
    this->currentDirectory = directory;
}


class CommandData
{
public:
    FileSystem *fileSystem;
    int port;
    bool ifServer; // 0 Client  1 Server
};


#endif
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include "include/File.h"

// FileChunk::FileChunk(const std::string &filePath, long long offset, int size, int id) : id(id)
// {
//     std::ifstream file(filePath, std::ios::binary);
//     if (file)
//     {
//         file.seekg(offset);
//         data.resize(size);
//         file.read(data.data(), size);
//     }
// }

// std::vector<char> &FileChunk::getData()
// {
//     return data;
// }

// bool FileChunk::save(const std::string &filePath)
// {
//     std::ofstream file(filePath, std::ios::binary);
//     if (file)
//     {
//         file.write(data.data(), data.size());
//         return true;
//     }
//     return false;
// }

// bool FileChunk::uploadChunk(Client *client)
// {
//     client->sendLargeData(data.data(), blockSize);
// }

// int FileChunk::getId() const
// {
//     return id;
// }

// File::File(const std::string &filePath, const std::string &outputDir, int blockSize, int firstChunkId)
//     : outputDir(outputDir), blockSize(blockSize), firstChunkId(firstChunkId)
// {
//     std::ifstream file(filePath, std::ios::binary);
//     if (file)
//     {
//         file.seekg(0, std::ios::end);
//         long long fileSize = file.tellg();
//         file.seekg(0, std::ios::beg);

//         int numChunks = fileSize / blockSize;
//         if (fileSize % blockSize != 0)
//         {
//             numChunks++;
//         }

//         for (int i = 0; i < numChunks; i++)
//         {
//             long long offset = i * blockSize;
//             int size = std::min(blockSize, static_cast<int>(fileSize - offset));
//             chunks.push_back(new FileChunk(filePath, offset, size, firstChunkId + i));
//         }
//     }
// }

// File::~File()
// {
//     for (FileChunk *chunk : chunks)
//     {
//         delete chunk;
//     }
// }

// bool File::splitFile()
// {
//     std::cout << "Splitting file into chunks..." << std::endl;

//     for (FileChunk *chunk : chunks)
//     {
//         std::string chunkFileName = outputDir + "/" + std::to_string(chunk->getId()) + ".chunk";
//         if (!chunk->save(chunkFileName))
//         {
//             std::cout << "Failed to save chunk " << chunk->getId() << std::endl;
//             return false;
//         }
//         std::cout << "Saved chunk " << chunk->getId() << std::endl;
//     }

//     std::cout << "Splitting file completed." << std::endl;
//     return true;
// }

// bool File::mergeFiles(const std::string &outputFilePath, const std::string &fileName)
// {
//     std::cout << "Merging chunks into file..." << std::endl;

//     std::ofstream outputFile(outputFilePath, std::ios::binary);
//     if (!outputFile)
//     {
//         std::cout << "Failed to create output file" << std::endl;
//         return false;
//     }

//     for (FileChunk *chunk : chunks)
//     {
//         std::string chunkFileName = outputDir + "/" + std::to_string(chunk->getId()) + ".chunk";
//         std::ifstream chunkFile(chunkFileName, std::ios::binary);
//         if (!chunkFile)
//         {
//             std::cout << "Failed to open chunk file " << chunk->getId() << std::endl;
//             return false;
//         }

//         outputFile << chunkFile.rdbuf();
//         chunkFile.close();

//         std::cout << "Merged chunk " << chunk->getId() << std::endl;
//     }

//     outputFile.close();

//     std::cout << "Merging chunks completed." << std::endl;
//     return true;
// }

// void File::splitAndUploadFile()
// {
//     if (splitFile())
//     {
//         for (FileChunk *chunk : chunks)
//         {
//             if (uploadChunk(chunk))
//             {
//                 std::cout << "Uploaded chunk " << chunk->getId() << std::endl;
//             }
//             else
//             {
//                 std::cout << "Failed to upload chunk " << chunk->getId() << std::endl;
//             }
//         }
//     }
// }

// bool File::mergeChunksAndDownload(const std::string &outputFilePath, const std::string &fileName)
// {
//     std::cout << "Merging and downloading chunks into file..." << std::endl;

//     std::ofstream outputFile(outputFilePath, std::ios::binary);
//     if (!outputFile)
//     {
//         std::cout << "Failed to create output file" << std::endl;
//         return false;
//     }

//     for (FileChunk *chunk : chunks)
//     {
//         if (!chunk->save(outputDir + "/" + std::to_string(chunk->getId()) + ".chunk"))
//         {
//             std::cout << "Failed to save chunk " << chunk->getId() << std::endl;
//             return false;
//         }
//         std::cout << "Saved chunk " << chunk->getId() << std::endl;
//     }

//     for (FileChunk *chunk : chunks)
//     {
//         std::string chunkFileName = outputDir + "/" + std::to_string(chunk->getId()) + ".chunk";
//         std::ifstream chunkFile(chunkFileName, std::ios::binary);
//         if (!chunkFile)
//         {
//             std::cout << "Failed to open chunk file " << chunk->getId() << std::endl;
//             return false;
//         }

//         outputFile << chunkFile.rdbuf();
//         chunkFile.close();

//         std::cout << "Merged chunk " << chunk->getId() << std::endl;
//     }

//     outputFile.close();

//     std::cout << "Merging and downloading chunks completed." << std::endl;
//     return true;
// }

// FileMetadata::FileMetadata(const std::string &fileId) : fileId(fileId)
// {
//     // Nothing to do here
// }

// FileMetadata::~FileMetadata()
// {
//     // Nothing to do here
// }

// std::string FileMetadata::getFileId() const
// {
//     return fileId;
// }

// std::string FileMetadata::getFileName() const
// {
//     return fileName;
// }

// void FileMetadata::setFileName(const std::string &fileName)
// {
//     this->fileName = fileName;
// }

// std::string FileMetadata::getFileType() const
// {
//     return fileType;
// }

// void FileMetadata::setFileType(const std::string &fileType)
// {
//     this->fileType = fileType;
// }

// std::string FileMetadata::getFileSize() const
// {
//     return fileSize;
// }

// void FileMetadata::setFileSize(const std::string &fileSize)
// {
//     this->fileSize = fileSize;
// }

// std::string FileMetadata::getCreationDate() const
// {
//     return creationDate;
// }

// void FileMetadata::setCreationDate(const std::string &creationDate)
// {
//     this->creationDate = creationDate;
// }

// void FileMetadata::setModifiedDate(const std::string &modifiedDate)
// {
//     this->modifiedDate = modifiedDate;
// }

// void testFileChunk()
// {
//     std::string filePath = "example";
//     long long offset = 0;
//     int size = 4*1024*1024;
//     int id = 1;

//     FileChunk fileChunk(filePath, offset, size, id);

//     std::vector<char> &data = fileChunk.getData();
//     for (char c : data)
//     {
//         std::cout << c;
//     }
//     std::cout << std::endl;

//     if (fileChunk.save("newfile.txt"))
//     {
//         std::cout << "FileChunk saved successfully" << std::endl;
//     }
//     else
//     {
//         std::cout << "FileChunk save failed" << std::endl;
//     }

//     std::cout << "FileChunk ID: " << fileChunk.getId() << std::endl;
// }

// int main()
// {
//     testFileChunk();
//     return 0;
// }

// void BlockOperator::save(const std::string &filePath)
// {
//     this->filePath = filePath;
//     std::ofstream file(filePath, std::ios::binary);
//     if (file)
//     {
//         file.write(data.data(), data.size());
//         //return true;
//     }
//     //return false;
// }

// void BlockOperator::remove()
// {
//     // 删除指定的文件
//     if (std::remove(this->filePath.c_str()) != 0) {
//         std::cout << "无法删除文件：" << this->filePath << std::endl;
//     } else {
//         std::cout << "成功删除文件：" << this->filePath << std::endl;
//     }
// }

// //已经连接好的TCP客户端
// void BlockOperator::backup(Client* client)
// {

// }

Block::Block()
{
    // this->id = (int *)mp_alloc(memoryPool, sizeof(int));
    // // this->sameOrigin=(Block* )mp_alloc(memoryPool, sizeof(Block));
    // this->data = (char *)mp_alloc(memoryPool, MAX_BLOCK_SIZE);
    // this->filePath = (std::string *)mp_alloc(memoryPool, sizeof(std::string));
}

Block::~Block()
{
    // delete (this->id);
    // delete (this->data);
    // delete (this->filePath);
}

void Block::setId(unsigned int id)
{
    this->id = id;
}

void Block::setData(char *data)
{
    this->data = data;
}

void Block::setFilePath(std::string filePath)
{
    this->filePath = filePath;
}

void Block::saveBlock()
{
    std::ofstream file(this->filePath, std::ios::binary);
    if (file)
    {
        file.write(this->data, strlen(this->data));
        std::cout << "save " << this->filePath << " sucess" << std::endl;
        // return true;
    }
    else
        std::cout << "save error";
    // return false;
}

void Block::removeBlock()
{
    // 删除指定的文件
    if (std::remove(this->filePath.c_str()) != 0)
    {
        std::cout << "无法删除文件：" << this->filePath << std::endl;
    }
    else
    {
        std::cout << "成功删除文件：" << this->filePath << std::endl;
    }
}

int Block::getId()
{
    return this->id;
}

char *Block::getData()
{
    return this->data;
}

int Block::getDataSize()
{
    return strlen(data);
}

std::string Block::getFilePath()
{
    return this->filePath;
}

// File::File(int id, std::string filePath, std::string outDir)
// {
//     this->id = id;
//     this->filePath = filePath;
//     this->outDir = outDir;
//     // this->id = (int *)mp_alloc(memoryPool, sizeof(int));
//     // this->Blockid=(int *)mp_alloc(memoryPool, sizeof(int));
//     // this->filePath = (std::string *)mp_alloc(memoryPool, sizeof(std::string));
//     // this->outDir = (std::string *)mp_alloc(memoryPool, sizeof(std::string));
//     // this->blocks = (Block *)mp_alloc(memoryPool, sizeof(Block));
// }

File::~File()
{
    // delete (this->id);
    // delete(this->Blockid);
    // delete(this->filePath);
    // delete (this->filePath);
    // delete (this->blocks);
}

unsigned int File::getId()
{
    return this->id;
}

std::string File::getFilePath()
{
    return this->filePath;
}

unsigned int *File::getBlockId()
{
    return this->BlockId;
}

std::string File::getOutDir()
{
    return this->outDir;
}
Block *File::getFirstBlock()
{
    return this->blocks;
}

int File::getNumBlocks()
{
    return this->numBlocks;
}

void File::setId(unsigned int id)
{
    this->id = id;
}

void File::setBlockId(unsigned int *BlockId)
{
    this->BlockId = BlockId;
}

void File::setFilePath(std::string filePath)
{
    this->filePath = filePath;
}

void File::setOutDir(std::string outDir)
{
    this->outDir = outDir;
}

void File::setBlocks(Block *blocks)
{
    this->blocks = blocks;
}

void File::setNumBlocks(int num)
{
    this->numBlocks = num;
}

void File::splitFile()
{
    std::ifstream inputFile(filePath, std::ios::binary); // 打开输入文件

    if (!inputFile.is_open())
    {
        std::cout << "Failed to open input file." << std::endl;
        return;
    }

    inputFile.seekg(0, std::ios::end); // 将文件指针移到文件末尾
    int fileSize = inputFile.tellg();  // 获取文件大小
    inputFile.seekg(0, std::ios::beg); // 将文件指针移到文件开头

    int numBlocks = (fileSize + MAX_BLOCK_SIZE - 1) / MAX_BLOCK_SIZE; // 计算需要的块数

    blocks = new Block[numBlocks]; // 创建块集合

    // std::cout<<fileSize<<std::endl<<numBlocks<<std::endl<<MAX_BLOCK_SIZE;
    for (int i = 0; i < numBlocks; i++)
    {
        blocks[i].set(BlockId[i]); // 设置块的id
        blocks[i].set(outDir + "/" + std::to_string(blocks[i].getId()));
        // std::cout<<blocks[i].getId()<<blocks[i].getFilePath();

        int blockSize = std::min(MAX_BLOCK_SIZE, fileSize); // 计算当前块的大小
        char *blockData = new char[blockSize];              // 创建块的数据向量

        inputFile.read(blockData, blockSize); // 从输入文件读取数据到块的数据向量
        // std::cout<<blockData;

        blocks[i].set(blockData); // 设置块的数据向量
        blocks[i].saveBlock();    // 将块保存到指定的实体文件路径

        fileSize -= blockSize; // 更新剩余文件大小
    }

    inputFile.close(); // 关闭输入文件
}

void File::mergeFile()
{
    std::ofstream outputFile(filePath, std::ios::binary); // 打开输出文件

    if (!outputFile.is_open())
    {
        std::cout << "Failed to open output file." << std::endl;
        return;
    }

    for (int i = 0; i < this->getNumBlocks(); i++)
    {
        std::string blockFilePath = outDir + "/" + std::to_string(BlockId[i]); // 构造块文件路径

        // std::cout<<blockFilePath;
        std::ifstream blockFile(blockFilePath, std::ios::binary); // 打开块文件
        if (!blockFile.is_open())
        {
            std::cout << "Failed to open block file: " << blockFilePath << std::endl;
            return;
        }

        // 获取文件大小
        blockFile.seekg(0, std::ios::end);
        std::streampos blockSize = blockFile.tellg();
        blockFile.seekg(0, std::ios::beg);
        char *blockData = new char[blockSize]; // 创建块的数据向量
        blockFile.read(blockData, blockSize);  // 从块文件读取数据到块的数据向量

        // std::cout<<blockSize<<std::endl;

        // // std::cout<<blockData;

        outputFile.write(blockData, blockSize); // 将块的数据向量写入输出文件

        blockFile.close(); // 关闭块文件
    }

    outputFile.close(); // 关闭输出文件
}

std::string File::getName()
{
    // 从文件路径中提取文件名
    std::size_t found = this->filePath.find_last_of("/");
    if (found != std::string::npos)
    {
        return filePath.substr(found + 1);
    }
    return "";
}

// Directory::Directory(int id, std::string directoryPath)
// {
//     this->id = id;
//     this->directoryPath = directoryPath;
// }

unsigned int Directory::getId()
{
    return this->id;
}

std::string Directory::getName()
{
    // 从文件路径中提取文件名
    std::size_t found = this->directoryPath.find_last_of("/");
    if (found != std::string::npos)
    {
        return directoryPath.substr(found + 1);
    }
    return "";
}

std::string Directory::getDirectoryPath()
{
    return this->directoryPath;
}

int Directory::getNumFiles()
{
    return this->numFiles;
}

int Directory::getNumSubdirectories()
{
    return this->numSubdirectories;
}

File **Directory::getFiles()
{
    return this->files;
}

Directory **Directory::getSubdirectories()
{
    return this->subdirectories;
}

void Directory::setId(unsigned int id)
{
    this->id = id;
}

void Directory::setDirectoryPath(std::string directoryPath)
{
    this->directoryPath = directoryPath;
}

void Directory::setNumFiles(int numFiles)
{
    this->numFiles = numFiles;
}

// void Directory::setFiles(File** files)
// {
//     this->files[]=files;
// }

void Directory::setNumSubdirectories(int numSubdirectories)
{
    this->numSubdirectories = numSubdirectories;
}

// void Directory::setSubdirectories(Directory *subdirectories[])
// {
//     this->subdirectories = subdirectories;
// }

void Directory::initial()
{
}

void Directory::addFile(File *file)
{

    this->files[numFiles++] = file;

    // Add file to the files array
}

void Directory::deleteFile(File *file)
{
    free(this->files[--numFiles]);
    // --this->numFiles;
    // Remove file from the files array
}

void Directory::addSubdirectory(Directory *directory)
{
    this->subdirectories[numSubdirectories++] = directory;
    // Add file to the files array
}

void Directory::deleteSubdirectory(Directory *directory)
{

    free(this->subdirectories[--numSubdirectories]);
    // Remove directory from the subdirectories array
}

File *Directory::findFileByName(std::string fileName)
{
    for (int i = 0; i < numFiles; i++)
    {
        if (files[i]->getName() == fileName)
        {
            return files[i];
        }
    }
    return nullptr;
}

File *Directory::findFileByPath(std::string path)
{
    // 拆分路径
    std::vector<std::string> directories;
    std::stringstream ss(path);
    std::string directory;
    while (std::getline(ss, directory, '/'))
    {
        directories.push_back(directory);
    }

    Directory *currentDirectory = this;
    for (int i = 0; i < directories.size() - 1; i++)
    {
        currentDirectory = currentDirectory->findSubdirectoryByName(directories[i]);
        if (currentDirectory == nullptr)
        {
            return nullptr;
        }
    }

    return currentDirectory->findFileByName(directories[directories.size() - 1]);
}

Directory *Directory::findSubdirectoryByName(std::string directoryName)
{
    for (int i = 0; i < numSubdirectories; i++)
    {
        if (subdirectories[i]->getName() == directoryName)
        {
            return subdirectories[i];
        }
    }
    return nullptr;
}

Directory *Directory::findSubdirectoryByPath(std::string path)
{
    if(numSubdirectories == 0)
        return nullptr;
    // 如果路径为空，则返回当前目录
    if (path.empty())
    {
        return this;
    }

    // 拆分路径为目录名和剩余路径
    size_t pos = path.find_last_of('/');
    std::string dirName = path.substr(0, pos-1);
    std::cout<<std::endl<<dirName<<std::endl;
    std::string remainingPath = (pos == std::string::npos) ? "" : path.substr(pos);

    // 在当前目录中查找子目录
    for (Directory *subdirectory : subdirectories)
    {
        if (subdirectory->getDirectoryPath() == dirName)
        {
            // 递归调用以查找剩余路径
            return subdirectory->findSubdirectoryByPath(remainingPath);
        }
    }
    // 如果找不到子目录，则返回nullptr
    return nullptr;
}
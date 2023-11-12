#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "include/File.h"

FileChunk::FileChunk(const std::string &filePath, long long offset, int size, int id) : id(id)
{
    std::ifstream file(filePath, std::ios::binary);
    if (file)
    {
        file.seekg(offset);
        data.resize(size);
        file.read(data.data(), size);
    }
}

std::vector<char> &FileChunk::getData()
{
    return data;
}

bool FileChunk::save(const std::string &filePath)
{
    std::ofstream file(filePath, std::ios::binary);
    if (file)
    {
        file.write(data.data(), data.size());
        return true;
    }
    return false;
}

int FileChunk::getId() const
{
    return id;
}

File::File(const std::string &filePath, const std::string &outputDir, int blockSize, int firstChunkId)
    : outputDir(outputDir), blockSize(blockSize), firstChunkId(firstChunkId)
{
    std::ifstream file(filePath, std::ios::binary);
    if (file)
    {
        file.seekg(0, std::ios::end);
        long long fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        int numChunks = fileSize / blockSize;
        if (fileSize % blockSize != 0)
        {
            numChunks++;
        }

        for (int i = 0; i < numChunks; i++)
        {
            long long offset = i * blockSize;
            int size = std::min(blockSize, static_cast<int>(fileSize - offset));
            chunks.push_back(new FileChunk(filePath, offset, size, firstChunkId + i));
        }
    }
}

File::~File()
{
    for (FileChunk *chunk : chunks)
    {
        delete chunk;
    }
}

bool File::splitFile()
{
    std::cout << "Splitting file into chunks..." << std::endl;

    for (FileChunk *chunk : chunks)
    {
        std::string chunkFileName = outputDir + "/" + std::to_string(chunk->getId()) + ".chunk";
        if (!chunk->save(chunkFileName))
        {
            std::cout << "Failed to save chunk " << chunk->getId() << std::endl;
            return false;
        }
        std::cout << "Saved chunk " << chunk->getId() << std::endl;
    }

    std::cout << "Splitting file completed." << std::endl;
    return true;
}

bool File::mergeFiles(const std::string &outputFilePath, const std::string &fileName)
{
    std::cout << "Merging chunks into file..." << std::endl;

    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile)
    {
        std::cout << "Failed to create output file" << std::endl;
        return false;
    }

    for (FileChunk *chunk : chunks)
    {
        std::string chunkFileName = outputDir + "/" + std::to_string(chunk->getId()) + ".chunk";
        std::ifstream chunkFile(chunkFileName, std::ios::binary);
        if (!chunkFile)
        {
            std::cout << "Failed to open chunk file " << chunk->getId() << std::endl;
            return false;
        }

        outputFile << chunkFile.rdbuf();
        chunkFile.close();

        std::cout << "Merged chunk " << chunk->getId() << std::endl;
    }

    outputFile.close();

    std::cout << "Merging chunks completed." << std::endl;
    return true;
}

bool File::uploadChunk(FileChunk *chunk)
{
    // TODO: Implement file chunk upload logic
    return true;
}

void File::splitAndUploadFile()
{
    if (splitFile())
    {
        for (FileChunk *chunk : chunks)
        {
            if (uploadChunk(chunk))
            {
                std::cout << "Uploaded chunk " << chunk->getId() << std::endl;
            }
            else
            {
                std::cout << "Failed to upload chunk " << chunk->getId() << std::endl;
            }
        }
    }
}

bool File::mergeChunksAndDownload(const std::string &outputFilePath, const std::string &fileName)
{
    std::cout << "Merging and downloading chunks into file..." << std::endl;

    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile)
    {
        std::cout << "Failed to create output file" << std::endl;
        return false;
    }

    for (FileChunk *chunk : chunks)
    {
        if (!chunk->save(outputDir + "/" + std::to_string(chunk->getId()) + ".chunk"))
        {
            std::cout << "Failed to save chunk " << chunk->getId() << std::endl;
            return false;
        }
        std::cout << "Saved chunk " << chunk->getId() << std::endl;
    }

    for (FileChunk *chunk : chunks)
    {
        std::string chunkFileName = outputDir + "/" + std::to_string(chunk->getId()) + ".chunk";
        std::ifstream chunkFile(chunkFileName, std::ios::binary);
        if (!chunkFile)
        {
            std::cout << "Failed to open chunk file " << chunk->getId() << std::endl;
            return false;
        }

        outputFile << chunkFile.rdbuf();
        chunkFile.close();

        std::cout << "Merged chunk " << chunk->getId() << std::endl;
    }

    outputFile.close();

    std::cout << "Merging and downloading chunks completed." << std::endl;
    return true;
}

FileMetadata::FileMetadata(const std::string &fileId) : fileId(fileId)
{
    // Nothing to do here
}

FileMetadata::~FileMetadata()
{
    // Nothing to do here
}

std::string FileMetadata::getFileId() const
{
    return fileId;
}

std::string FileMetadata::getFileName() const
{
    return fileName;
}

void FileMetadata::setFileName(const std::string &fileName)
{
    this->fileName = fileName;
}

std::string FileMetadata::getFileType() const
{
    return fileType;
}

void FileMetadata::setFileType(const std::string &fileType)
{
    this->fileType = fileType;
}

std::string FileMetadata::getFileSize() const
{
    return fileSize;
}

void FileMetadata::setFileSize(const std::string &fileSize)
{
    this->fileSize = fileSize;
}

std::string FileMetadata::getCreationDate() const
{
    return creationDate;
}

void FileMetadata::setCreationDate(const std::string &creationDate)
{
    this->creationDate = creationDate;
}



void FileMetadata::setModifiedDate(const std::string &modifiedDate)
{
    this->modifiedDate = modifiedDate;
}
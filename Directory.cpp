#include "Directory.h"

DirectoryMetadata::DirectoryMetadata(const std::string &directoryId)
    : directoryId(directoryId) {}

DirectoryMetadata::~DirectoryMetadata() {}

std::string DirectoryMetadata::getDirectoryId() const
{
    return directoryId;
}

void DirectoryMetadata::setDirectoryId(const std::string &directoryId)
{
    this->directoryId = directoryId;
}

std::string DirectoryMetadata::getDirectoryName() const
{
    return directoryName;
}

void DirectoryMetadata::setDirectoryName(const std::string &directoryName)
{
    this->directoryName = directoryName;
}

std::string DirectoryMetadata::getParentDirectoryId() const
{
    return parentDirectoryId;
}

void DirectoryMetadata::setParentDirectoryId(const std::string &parentDirectoryId)
{
    this->parentDirectoryId = parentDirectoryId;
}

std::string DirectoryMetadata::getCreationDate() const
{
    return creationDate;
}

void DirectoryMetadata::setCreationDate(const std::string &creationDate)
{
    this->creationDate = creationDate;
}

std::string DirectoryMetadata::getModifiedDate() const
{
    return modifiedDate;
}

void DirectoryMetadata::setModifiedDate(const std::string &modifiedDate)
{
    this->modifiedDate = modifiedDate;
}

Directory::Directory(const std::string &path, const DirectoryMetadata &metadata)
    : path_(path), metadata_(metadata) {}

std::string Directory::getPath() const
{
    return path_;
}

std::string Directory::getName() const
{
    // 获取路径中最后一个目录的名称
    size_t pos = path_.find_last_of("/");
    if (pos != std::string::npos)
    {
        return path_.substr(pos + 1);
    }
    return "";
}

std::vector<std::string> Directory::getFiles() const
{
    // 返回目录中的文件列表
    std::vector<std::string> files;
    // 实现获取文件列表的逻辑
    return files;
}

std::vector<std::string> Directory::getSubdirectories() const
{
    // 返回目录中的子目录列表
    std::vector<std::string> subdirectories;
    // 实现获取子目录列表的逻辑
    return subdirectories;
}

bool Directory::createSubdirectory(const std::string &name)
{
    // 创建子目录
    // 实现创建子目录的逻辑
    return true;
}

bool Directory::deleteSubdirectory(const std::string &name)
{
    // 删除子目录
    // 实现删除子目录的逻辑
    return true;
}

bool Directory::createFile(const std::string &name)
{
    // 创建文件
    // 实现创建文件的逻辑
    return true;
}

bool Directory::deleteFile(const std::string &name)
{
    // 删除文件
    // 实现删除文件的逻辑
    return true;
}

bool Directory::renameFile(const std::string &oldName, const std::string &newName)
{
    // 重命名文件
    // 实现重命名文件的逻辑
    return true;
}

bool Directory::moveFile(const std::string &fileName, const std::string &destinationPath)
{
    // 移动文件到目标路径
    // 实现移动文件的逻辑
    return true;
}

const DirectoryMetadata &Directory::getMetadata() const
{
    return metadata_;
}

void Directory::setMetadata(const DirectoryMetadata &metadata)
{
    metadata_ = metadata;
}

bool Directory::isValidPath(const std::string &path)
{
    // 检查路径是否有效
    // 实现检查路径有效性的逻辑
    return true;
}

bool Directory::isDirectory(const std::string &path)
{
    // 检查路径是否为目录
    // 实现检查路径是否为目录的逻辑
    return true;
}
#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>

class DirectoryMetadata {
public:
    DirectoryMetadata(const std::string& directoryId);
    ~DirectoryMetadata();

    std::string getDirectoryId() const;
    void setDirectoryId(const std::string& directoryId);

    std::string getDirectoryName() const;
    void setDirectoryName(const std::string& directoryName);

    std::string getParentDirectoryId() const;
    void setParentDirectoryId(const std::string& parentDirectoryId);

    std::string getCreationDate() const;
    void setCreationDate(const std::string& creationDate);

    std::string getModifiedDate() const;
    void setModifiedDate(const std::string& modifiedDate);

    // 添加其他常见的元数据属性和相应的访问和更新方法

private:
    std::string directoryId;
    std::string directoryName;
    std::string parentDirectoryId;
    std::string creationDate;
    std::string modifiedDate;

    // 其他常见的元数据属性
};

class Directory {
public:
    Directory(const std::string& path, const DirectoryMetadata& metadata);

    std::string getPath() const;
    std::string getName() const;
    std::vector<std::string> getFiles() const;
    std::vector<std::string> getSubdirectories() const;
    bool createSubdirectory(const std::string& name);
    bool deleteSubdirectory(const std::string& name);
    bool createFile(const std::string& name);
    bool deleteFile(const std::string& name);
    bool renameFile(const std::string& oldName, const std::string& newName);
    bool moveFile(const std::string& fileName, const std::string& destinationPath);

    const DirectoryMetadata& getMetadata() const;
    void setMetadata(const DirectoryMetadata& metadata);

private:
    std::string path_;
    DirectoryMetadata metadata_;

    bool isValidPath(const std::string& path);
    bool isDirectory(const std::string& path);
};

class BPlusTree
{
public:
    BPlusTree();
    ~BPlusTree();

    void insert(const std::string &key, const std::string &value);
    void remove(const std::string &key);
    std::string search(const std::string &key);

private:
    // 定义B+树的节点结构
    struct Node
    {
        bool isLeaf;
        std::vector<std::string> keys;
        std::vector<std::string> values;
        std::vector<Node *> children;

        Node(bool isLeaf);
        ~Node();
    };

    Node *root_;
    int degree_;

    void splitChild(Node *parent, int index);
    void insertNonFull(Node *node, const std::string &key, const std::string &value);
    void remove(Node *node, const std::string &key);
    std::string search(Node *node, const std::string &key);
};

#endif // DIRECTORY_H

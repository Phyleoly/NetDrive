#include "include/IDHandler.h"
#include <iostream>
#include <random>
#include <sstream>

FileSystemIDHandler::FileSystemIDHandler() {}

std::string FileSystemIDHandler::generateID(FileType type)
{
    std::string id = generateRandomID();
    usedIDs.insert(id);
    idTypeMap[id] = type;
    return id;
}

bool FileSystemIDHandler::isValidID(const std::string &id)
{
    return usedIDs.count(id) > 0;
}

FileType FileSystemIDHandler::parseIDType(const std::string &id)
{
    if (idTypeMap.count(id) > 0)
    {
        return idTypeMap[id];
    }
    return FileType::File;
}

std::string FileSystemIDHandler::generateRandomID()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    std::stringstream ss;
    for (int i = 0; i < 10; ++i)
    {
        ss << dis(gen);
    }
    return ss.str();
}

size_t FileSystemIDHandler::calculateIDHash(const std::string &id)
{
    std::hash<std::string> hasher;
    return hasher(id);
}
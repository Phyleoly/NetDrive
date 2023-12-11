#ifndef CONSISTENT_HASHING_H
#define CONSISTENT_HASHING_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

typedef std::uint32_t (*HashFunc)(const std::string&);

class ConsistentHashing {
public:
    ConsistentHashing(HashFunc hashFunc);


    void addNode(const std::string& node);
    void removeNode(const std::string& node);
    std::string getNode(const std::string& data);

    std::vector<std::string> getAllNodes();
    std::vector<std::string> getReplicaNodes(const std::string& node, std::size_t numReplicas);
    std::size_t getNumNodes();
    std::size_t getNumReplicas();

private:
    HashFunc hashFunc_;
    std::map<std::uint32_t, std::string> nodeMap_;
    std::size_t numReplicas_;

    std::uint32_t hash(const std::string& data);
}; 

#endif // CONSISTENT_HASHING_H

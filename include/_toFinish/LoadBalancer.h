#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include <string>

struct Node {
    std::string address;
    int currentLoad;
    int maxLoad;
    int weight;
    bool healthy;

    Node(const std::string& addr, int maxL, int wt);
};

class LoadBalancer {
public:
    LoadBalancer();

    void addNode(const std::string& address, int maxLoad, int weight);
    void removeNode(const std::string& address);
    void updateLoad(const std::string& address, int newLoad);
    std::string selectNode();

private:
    std::vector<Node> nodes;
    int totalLoad;
    std::string loadBalanceAlgorithm;

    std::string roundRobinAlgorithm();
    std::string weightedRoundRobinAlgorithm();
    std::string leastConnectionAlgorithm();
    std::string randomAlgorithm();
};

#endif // LOAD_BALANCER_H

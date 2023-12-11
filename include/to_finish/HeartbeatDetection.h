#ifndef HEARTBEAT_DETECTION_H
#define HEARTBEAT_DETECTION_H

#include <vector>
#include <functional>
#include <string>
#include <chrono>
#include <thread>

class HeartbeatDetection {
public:
    HeartbeatDetection();
    ~HeartbeatDetection();
    
    void startDetection();  // 启动心跳检测
    void stopDetection();   // 停止心跳检测
    
    bool isHeartbeatDetected();  // 返回是否检测到心跳
    
    void registerServer(const std::string& serverName, const std::function<void()>& onHeartbeatLost);  // 注册服务器，指定心跳丢失时的回调函数
    
private:
    struct Server {
        std::string name;
        std::function<void()> onHeartbeatLost;
        bool heartbeatDetected;
        std::chrono::steady_clock::time_point lastHeartbeatTime;
    };
    
    bool heartbeatDetected;  // 表示是否检测到心跳
    std::vector<Server> servers;  // 存储已注册的服务器
    
    std::thread detectionThread;  // 心跳检测线程
    bool stopFlag;  // 停止心跳检测的标志
    
    void detectHeartbeat();  // 检测心跳的具体实现，可以是一个循环，定期检测是否有心跳信号
    
    // 其他辅助方法，例如初始化、清理等
};

#endif  // HEARTBEAT_DETECTION_H

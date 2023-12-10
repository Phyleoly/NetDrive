#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <queue>
#include <functional>

class ThreadPool
{
public:
    ThreadPool(int numThreads);
    ~ThreadPool();

    void addTask(std::function<void()> task);

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mutex;
    std::condition_variable cv;
    bool stop;
};

#endif
#include "include/ThreadPool.h"

ThreadPool::ThreadPool(int numThreads) : stop(false)
{
    for (int i = 0; i < numThreads; ++i)
    {
        threads.emplace_back([this]()
                             {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    cv.wait(lock, [this]() { return stop || !tasks.empty(); });
                    if (stop && tasks.empty()) {
                        return;
                    }
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            } });
    }
}



ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(mutex);
        stop = true;
    }
    cv.notify_all();
    for (std::thread &thread : threads)
    {
        thread.detach();
    }
}

void ThreadPool::addTask(std::function<void()> task)
{
    {
        std::unique_lock<std::mutex> lock(mutex);
        tasks.push(std::move(task));
    }
    cv.notify_one();
}


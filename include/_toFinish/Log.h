#ifndef LOG_H
#define LOG_H

#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <mutex>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

struct LogEntry {
    LogLevel level;
    std::string message;
    std::string location;
};

class Log {
public:
    Log();
    ~Log();

    void log(const LogEntry& logEntry);
    void addLog(const LogEntry& logEntry);
    void clearLogs();
    bool hasLogs() const;
    std::vector<LogEntry> getLogEntries() const;

    void addLogHandler(const std::function<void(const LogEntry&)>& logHandler);
    void setMinLogLevel(LogLevel minLogLevel);
    void setLogFile(const std::string& filename);
    void setMaxFileSize(std::size_t maxFileSize);
    void setMaxFileAge(std::size_t maxFileAge);

private:
    std::vector<LogEntry> m_logEntries;
    std::vector<std::function<void(const LogEntry&)>> m_logHandlers;
    LogLevel m_minLogLevel;
    std::ofstream m_logFile;
    std::size_t m_maxFileSize;
    std::size_t m_maxFileAge;
    std::mutex m_mutex;

    void rotateLogFile();
    std::string getCurrentTimestamp();
};

#endif // LOG_H

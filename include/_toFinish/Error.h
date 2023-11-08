#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <string>
#include <vector>
#include <fucntional>

enum class ErrorLevel {
    INFO,
    WARNING,
    ERROR
};

struct ErrorInfo {
    ErrorLevel level;
    std::string code;
    std::string message;
    std::string location;
};

class ErrorHandler {
public:
    ErrorHandler();
    ~ErrorHandler();

    void setError(const ErrorInfo& errorInfo);
    void addError(const ErrorInfo& errorInfo);
    void clearErrors();
    bool hasErrors() const;
    std::vector<ErrorInfo> getErrorMessages() const;

    // 添加错误处理的回调函数
    void addErrorHandler(const std::function<void(const ErrorInfo&)>& errorHandler);

private:
    std::vector<ErrorInfo> m_errorMessages;
    std::vector<std::function<void(const ErrorInfo&)>> m_errorHandlers;
};

#endif // ERROR_HANDLER_H

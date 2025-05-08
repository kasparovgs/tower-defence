#ifndef GAMEOVEREXCEPTION_H
#define GAMEOVEREXCEPTION_H

#include <exception>

class GameOverException: public std::exception {
private:
    std::string message_;
public:
    explicit GameOverException(const std::string& message) : message_(message) {}
    const char* what() const noexcept override { return message_.c_str(); }
};

#endif

#ifndef TULZ_EXCEPTION_H
#define TULZ_EXCEPTION_H

#include <exception>
#include <string>

namespace tulz {
class Exception: public std::exception {
public:
    int type;
    std::string message;

    explicit Exception(const std::string &message, int type = -1);

    const char* what() const noexcept override;
};
}

#endif //TULZ_EXCEPTION_H

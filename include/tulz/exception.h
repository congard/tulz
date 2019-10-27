#ifndef TULZ_EXCEPTION_
#define TULZ_EXCEPTION_H

#include <exception>
#include <string>

namespace tulz {
class Exception: public std::exception {
public:
    int type;
    std::string message;

    explicit Exception(const std::string &message, int type = -1);

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};
}

#endif //TULZ_EXCEPTION_

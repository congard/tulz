#include "tulz/exception.h"

namespace tulz {
Exception::Exception(const std::string &message, const int type) {
    this->message = message;
    this->type = type;
}

const char* Exception::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
    return message.c_str();
}
}
#include "tulz/Exception.h"

namespace tulz {
Exception::Exception(const std::string &message, const int type) {
    this->message = message;
    this->type = type;
}

const char* Exception::what() const noexcept {
    return message.c_str();
}
}
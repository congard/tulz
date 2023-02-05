#ifndef TULZ_TESTDETAILS_H
#define TULZ_TESTDETAILS_H

#include <functional>
#include <string>

namespace tulz {
struct TestDetails {
    std::string name;
    std::function<void(const TestDetails&)> test;
};
}

#endif //TULZ_TESTDETAILS_H

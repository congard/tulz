#ifndef TULZ_TEST_H
#define TULZ_TEST_H

#include <functional>
#include <forward_list>
#include <string>

#include "TestDetails.h"

namespace tulz {
class Test {
protected:
    std::forward_list<TestDetails> m_tests;
    std::forward_list<TestDetails>::iterator m_lastTest {m_tests.before_begin()};
    std::string m_testName;

protected:
    explicit inline Test(std::string_view name)
        : m_testName(name) {}

    void addTest(const TestDetails &test);

    static void assertTrueImpl(
        const std::function<bool()> &func,
        std::string_view testName, int line,
        std::string_view desc = "Assertion failed");

public:
    void runTests();
};

#define TEST_CLASS(name, ...) \
class name: public tulz::Test { \
public:                       \
    explicit name(void *data = nullptr): tulz::Test(#name) \
        __VA_ARGS__           \
};

#define TEST(testName, ...) \
addTest(tulz::TestDetails{ .name = #testName, .test = [=](const tulz::TestDetails &_details) __VA_ARGS__ });

#define expr(...) [&]() -> bool { return __VA_ARGS__; }
#define assertTrueExprDesc(e, desc) assertTrueImpl(e, _details.name, __LINE__, desc)
#define assertTrueExpr(e) assertTrueExprDesc(e, "Assertion failed")
#define assertTrue(...) assertTrueExpr(expr(__VA_ARGS__))

}

#endif //TULZ_TEST_H

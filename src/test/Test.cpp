#include <tulz/test/Test.h>

#include <exception>
#include <stdexcept>
#include <chrono>

namespace tulz {
void Test::addTest(const TestDetails &test) {
    m_tests.emplace_after(m_lastTest, test);
    ++m_lastTest;
}

void Test::assertTrueImpl(const std::function<bool()> &func, std::string_view testName, int line, std::string_view desc) {
    auto printFailedMessage = [&]() {
        fprintf(stderr, "Assertion failed in test %s on line %i\n", testName.data(), line);
    };

    try {
        if (!func()) {
            throw -1;
        }
    } catch (const std::exception &e) {
        printFailedMessage();
        throw e;
    } catch (...) {
        printFailedMessage();
        throw std::runtime_error(desc.data());
    }
}

inline long time() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Test::runTests() {
    if (!m_testName.empty())
        printf("Running tests: %s\n", m_testName.c_str());

    auto testsCount = static_cast<int>(std::distance(m_tests.begin(), m_tests.end()));
    int testNumber = 0;
    int failedTestsCount = 0;

    auto startTime = time();

    for (const auto &testDetails : m_tests) {
        ++testNumber;

        const auto &testName = testDetails.name;

        auto testFailed = [&](std::string_view reason) {
            fprintf(stderr, "[%i/%i] Test %s failed, reason: %s\n",
                    testNumber, testsCount, testName.c_str(), reason.data());
            ++failedTestsCount;
        };

        try {
            testDetails.test(testDetails);
            fprintf(stdout, "[%i/%i] Test %s passed\n", testNumber, testsCount, testName.c_str());
        } catch (const std::exception &e) {
            testFailed(e.what());
        } catch (...) {
            testFailed("other");
        }
    }

    printf("%i tests passed, %i tests failed, %i total\n",
           testsCount - failedTestsCount, failedTestsCount, testsCount);
    printf("Done in %li ms\n", time() - startTime);
}
}

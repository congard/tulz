# Tulz::Test

Basic & lightweight component for unit testing

## Usage

```c++
#include <tulz/test/Test.h>
#include <stdexcept>

TEST_CLASS(TestExample, {
    TEST(TestOk, {
        int a = 5;
        int b = 5;
        assertTrue(a == b);
    })

    TEST(TestAssertionFailed, {
        assertTrue(false);
    })

    TEST(TestError, {
        throw std::runtime_error("Test that throws an error!");
    })
})

int main() {
    TestExample().runTests();
    return 0;
}
```

Possible output:

```
Running tests: TestExample
[1/3] Test TestOk passed
Assertion failed in test TestFailure on line 12
[2/3] Test TestAssertionFailed failed, reason: Assertion failed
[3/3] Test TestError failed, reason: Test that throws an error!
1 tests passed, 2 tests failed, 3 total
Done in 0 ms
```

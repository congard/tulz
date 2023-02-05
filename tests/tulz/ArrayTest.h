#ifndef TULZ_ARRAY_TEST_H
#define TULZ_ARRAY_TEST_H

#include <tulz/Array.h>
#include <tulz/test/Test.h>

TEST_CLASS(ArrayTest, {
    TEST(InitializerList, {
        tulz::Array<int> array {0, 1, 2, 3};
        assertTrue(array.size() == 4);

        for (int i = 0; i < array.size(); ++i) {
            assertTrue(array[i] == i);
        }
    })

    TEST(InitWithValue, {
        tulz::Array<int> array(5, 123);
        assertTrue(array.size() == 5);

        for (int i : array) {
            assertTrue(i == 123);
        }
    })

    TEST(Iterator, {
        tulz::Array<int> array {0, 1, 2, 3};
        auto it = array.begin();

        assertTrue(*it == 0);
        assertTrue(*(++it) == 1);
        assertTrue(*(++it) == 2);
        assertTrue(*(++it) == 3);
        assertTrue(*(--it) == 2);
    })

    TEST(Distance, {
        tulz::Array<int> array(5);
        auto size = array.size();
        auto distance = std::distance(array.begin(), array.end());
        assertTrue(size == distance);
    })

    TEST(Classes, {
        tulz::Array<std::string> array(2);
        array[0] = std::string("foo");
        array[1] = std::string("bar");

        assertTrue(array[0] == "foo");
        assertTrue(array[1] == "bar");
    })
})

#endif //TULZ_ARRAY_TEST_H

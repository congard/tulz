#include <tulz/demangler.h>
#include <gtest/gtest.h>

// basic
struct Foo {};
class Bar {};

// namespace
namespace ns {
struct Foo {};
class Bar {};
}

// nested
namespace nested {
struct Foo {
    struct Bar {};
    enum Baz {};
    enum class Qux {};
};
}

// template
namespace temp {
template<typename T> struct Foo {};
struct Bar {};
}

// confusing names
struct struct_right {};
struct left_struct {};
struct left_struct_right {};

namespace dmg = tulz::demangler;

TEST(DemanglerTest, Basic) {
    EXPECT_STREQ(dmg::demangle(typeid(Foo).name()).c_str(), "Foo");
    EXPECT_STREQ(dmg::demangle(typeid(Bar).name()).c_str(), "Bar");
}

TEST(DemanglerTest, Namespace) {
    EXPECT_STREQ(dmg::demangle(typeid(ns::Foo).name()).c_str(), "ns::Foo");
    EXPECT_STREQ(dmg::demangle(typeid(ns::Bar).name()).c_str(), "ns::Bar");
}

TEST(DemanglerTest, Nesting) {
    EXPECT_STREQ(dmg::demangle(typeid(nested::Foo::Bar).name()).c_str(), "nested::Foo::Bar");
    EXPECT_STREQ(dmg::demangle(typeid(nested::Foo::Baz).name()).c_str(), "nested::Foo::Baz");
    EXPECT_STREQ(dmg::demangle(typeid(nested::Foo::Qux).name()).c_str(), "nested::Foo::Qux");
}

TEST(DemanglerTest, Template) {
    EXPECT_STREQ(dmg::demangle(typeid(temp::Foo<temp::Bar>).name()).c_str(), "temp::Foo<temp::Bar>");
}

// This test was created for Windows, since on Windows
// demangled names come with keywords (struct, class, enum)
// which need to be removed.
TEST(DemanglerTest, ConfusingNames) {
    EXPECT_STREQ(dmg::demangle(typeid(struct_right).name()).c_str(), "struct_right");
    EXPECT_STREQ(dmg::demangle(typeid(left_struct).name()).c_str(), "left_struct");
    EXPECT_STREQ(dmg::demangle(typeid(left_struct_right).name()).c_str(), "left_struct_right");
}

TEST(DemanglerTest, Primitives) {
    EXPECT_STREQ(dmg::demangle(typeid(int).name()).c_str(), "int");
    EXPECT_STREQ(dmg::demangle(typeid(const int).name()).c_str(), "int");
    EXPECT_STREQ(dmg::demangle(typeid(long int).name()).c_str(), "long");
}

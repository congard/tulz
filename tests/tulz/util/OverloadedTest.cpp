#include <gtest/gtest.h>

#include <variant>
#include <string>

#include <tulz/util/overloaded.h>

TEST(OverloadedTest, CoverAll) {
    std::variant<int, float, std::string> variant;
    variant = 3.14f;

    enum class VisitedType {
        None,
        Int,
        Float,
        String
    };

    VisitedType visitedType {VisitedType::None};

    std::visit(tulz::overloaded {
        [&](int) { visitedType = VisitedType::Int; },
        [&](float) { visitedType = VisitedType::Float; },
        [&](const std::string&) { visitedType = VisitedType::String; }
    }, variant);

    ASSERT_EQ(visitedType, VisitedType::Float);
}
cmake_minimum_required(VERSION 3.14)
project(tulz-tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

if (UNIX)
    set(DEPS_DIR "deps")
elseif (WIN32)
    set(DEPS_DIR "deps-win")
else()
    message(FATAL_ERROR "Unsupported OS")
endif()

get_filename_component(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${DEPS_DIR}" REALPATH)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_subdirectory(../ tulz)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

function(add_gtest name src)
    add_executable(${name} "${src}")
    target_link_libraries(${name} gtest gtest_main tulz)
    target_include_directories(${name} PUBLIC ../include)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

add_gtest(ArrayTest tulz/container/ArrayTest.cpp)
add_gtest(RingBufferTest tulz/container/RingBufferTest.cpp)
add_gtest(RingBufferEfficiencyTest tulz/container/RingBufferEfficiencyTest.cpp)

add_gtest(DemanglerTest tulz/demangler_test.cpp)

add_gtest(RoutingKeyBuilderTest tulz/observer/routing/RoutingKeyBuilderTest.cpp)
add_gtest(RoutingLevelViewTest tulz/observer/routing/RoutingLevelViewTest.cpp)
add_gtest(SubjectRouterTest tulz/observer/routing/SubjectRouterTest.cpp)
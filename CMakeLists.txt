cmake_minimum_required(VERSION 3.10)
project(tulz)

set(CMAKE_CXX_STANDARD 14)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
endif()

include_directories(include)

add_library(tulz
        include/tulz/Path.h src/Path.cpp
        include/tulz/Array.h
        include/tulz/StringUtils.h src/StringUtils.cpp
        include/tulz/macros.h
        include/tulz/File.h src/File.cpp
        include/tulz/Exception.h src/Exception.cpp
        include/tulz/DirectoryVisitor.h src/DirectoryVisitor.cpp
        include/tulz/DynamicLibrary.h src/DynamicLibrary.cpp
        include/tulz/threading/Mutex.h src/threading/Mutex.cpp
        include/tulz/threading/MutexLocker.h src/threading/MutexLocker.cpp
        include/tulz/threading/Runnable.h src/threading/Runnable.cpp
        include/tulz/threading/Thread.h src/threading/Thread.cpp
        include/tulz/threading/ThreadPool.h src/threading/ThreadPool.cpp)

if (UNIX AND NOT ANDROID)
    set(LINK_LIBRARIES pthread)
endif()

target_link_libraries(tulz ${LINK_LIBRARIES})

add_executable(tulz-examples examples/example.cpp)

target_link_libraries(tulz-examples tulz)

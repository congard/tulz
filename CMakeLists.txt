cmake_minimum_required(VERSION 3.15)
project(tulz)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(tulz
        include/tulz/Path.h src/Path.cpp
        include/tulz/Array.h
        include/tulz/StringUtils.h src/StringUtils.cpp
        include/tulz/macros.h
        include/tulz/File.h src/File.cpp
        include/tulz/Exception.h src/Exception.cpp
        include/tulz/DirectoryVisitor.h src/DirectoryVisitor.cpp)
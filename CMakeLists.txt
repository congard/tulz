cmake_minimum_required(VERSION 3.15)
project(tulz)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(tulz
        src/path.cpp
        include/tulz/path.h
        include/tulz/array.h
        src/string_utils.cpp
        include/tulz/string_utils.h
        include/tulz/Array
        include/tulz/Path
        include/tulz/StringUtils
        include/tulz/macros.h
        src/file.cpp
        include/tulz/file.h
        include/tulz/File
        src/exception.cpp
        include/tulz/exception.h
        include/tulz/Exception)
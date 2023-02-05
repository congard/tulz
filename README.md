# Tulz

Tulz is cross-platform C++17 tools library for C++ development

## Compilers support

Tested under:

| Linux | Windows              | Android          |
|-------|----------------------|------------------|
| GCC   | MSVC 19.26.28806 x64 | NDK 22.0.7026061 |
| CLang | GCC 8.1.0, MinGW-w64 |                  |
|       | CLang 10.0.0         |                  |

## Installation

1. Put sources in your libs folder
2. Add tulz to your project `add_subdirectory(your_libs_folder/tulz)`
3. After `add_executable(your_project ...)` add `target_link_libraries(your_project tulz)`

## Components

1. [test](include/tulz/test)
2. [threading](include/tulz/threading)
3. io
4. dll

## Examples

You can find example in [examples/example.cpp](examples/example.cpp)

Note that you must clone this repository to `tulz` directory to be able to run example, not `tulz-master` etc

## Donate

<b>Payeer:</b> P36281059

# Tulz

Tulz is cross-platform C++17 tools library for C++ development.
It contains reusable classes that I use in my projects. 

## Compilers support

Tested under:

| Linux | Windows              | Android          |
|-------|----------------------|------------------|
| GCC   | MSVC 19.37.32824 x64 | NDK 22.0.7026061 |
| Clang | Clang 16.0.0         |                  |

## Installation

1. Put sources in your libs folder
2. Add tulz to your project `add_subdirectory(your_libs_folder/tulz)`
3. After `add_executable(your_project ...)` add `target_link_libraries(your_project tulz)`

## Components

1. [observer](include/tulz/observer)
2. [test](include/tulz/test) **\[Deprecated\]**
3. [threading](include/tulz/threading)
4. io
5. dll

## Flags

| Flag                                   | Description                              | Mandatory | Default | Platform |
|----------------------------------------|------------------------------------------|-----------|---------|----------|
| `TULZ_DEMANGLER_DISABLE_THREAD_SAFETY` | Controls `tulz::demangler` thread safety | No        | OFF     | Windows  |

## Examples

You can find example in [examples/example.cpp](examples/example.cpp)

Note that you must clone this repository to `tulz` directory to be able to run example, not `tulz-master` etc

## Donate

<b>Payeer:</b> P36281059

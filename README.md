# Tulz

Tulz is a light-weight cross-platform C++20 tools library for C++ development.
It contains reusable classes that I use in my projects. 

## Installation

1. Put sources in your libs folder
2. Add tulz to your project `add_subdirectory(your_libs_folder/tulz)`
3. After `add_executable(your_project ...)` add `target_link_libraries(your_project tulz)`

## Components

1. [container](include/tulz/container)
2. [observer](include/tulz/observer)
3. [threading](include/tulz/threading)
4. io
5. dll

## Flags

| Flag                                   | Description                              | Mandatory | Default | Platform |
|----------------------------------------|------------------------------------------|-----------|---------|----------|
| `TULZ_DEMANGLER_DISABLE_THREAD_SAFETY` | Controls `tulz::demangler` thread safety | No        | OFF     | Windows  |
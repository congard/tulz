cmake_minimum_required(VERSION 3.10)
project(tulz)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
endif()

include_directories(include)

set(TULZ_SOURCES
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
        include/tulz/threading/ThreadPool.h src/threading/ThreadPool.cpp
        src/LocaleInfo.cpp include/tulz/LocaleInfo.h
        src/test/Test.cpp include/tulz/test/Test.h
        include/tulz/test/TestDetails.h)

if (ANDROID)
    set(TULZ_ANDROID_SOURCES
            android/src/assets/AssetManager.cpp android/include/tulz/assets/AssetManager.h
            android/src/assets/Asset.cpp android/include/tulz/assets/Asset.h
            android/src/assets/AssetDir.cpp android/include/tulz/assets/AssetDir.h)

    include_directories(android/include)
endif()

add_library(tulz
        ${TULZ_SOURCES}
        ${TULZ_ANDROID_SOURCES})

if (UNIX AND NOT ANDROID)
    set(LINK_LIBRARIES ${LINK_LIBRARIES} pthread)
endif()

if (ANDROID)
    set(LINK_LIBRARIES ${LINK_LIBRARIES} android)
endif()

target_link_libraries(tulz ${LINK_LIBRARIES})

add_executable(tulz-examples examples/example.cpp)

target_link_libraries(tulz-examples tulz)

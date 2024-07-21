cmake_minimum_required(VERSION 3.10)
project(tulz)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(TULZ_SOURCES
        include/tulz/Path.h src/Path.cpp
        include/tulz/container/Array.h
        include/tulz/StringUtils.h src/StringUtils.cpp
        include/tulz/util/macros.h
        include/tulz/File.h src/File.cpp
        include/tulz/Exception.h src/Exception.cpp
        include/tulz/DirectoryVisitor.h src/DirectoryVisitor.cpp
        include/tulz/DynamicLibrary.h src/DynamicLibrary.cpp
        include/tulz/threading/Runnable.h src/threading/Runnable.cpp
        include/tulz/threading/Thread.h src/threading/Thread.cpp
        include/tulz/threading/ThreadPool.h src/threading/ThreadPool.cpp
        src/LocaleInfo.cpp include/tulz/LocaleInfo.h
        include/tulz/observer/Observer.h
        include/tulz/observer/Subject.h
        include/tulz/observer/Subscription.h
        include/tulz/observer/Observable.h
        include/tulz/observer/ObservableNumber.h
        include/tulz/util/static_initializer.h
        include/tulz/observer/USubscription.h
        include/tulz/demangler.h
        src/demangler.cpp
        include/tulz/container/RingBuffer.h
        include/tulz/container/RandomAccessIndexIterator.h
        include/tulz/util/noncopyable.h
        include/tulz/util/nonmovable.h
        src/observer/routing/RoutingKey.cpp
        include/tulz/observer/routing/RoutingKey.h
        src/observer/routing/RoutingLevelView.cpp
        include/tulz/observer/routing/RoutingLevelView.h
        src/observer/routing/RoutingKeyBuilder.cpp
        include/tulz/observer/routing/RoutingKeyBuilder.h
        include/tulz/observer/routing/RoutingKeyLevel.h
        src/observer/routing/SubjectRouter.cpp
        include/tulz/observer/routing/SubjectRouter.h
        include/tulz/export.h
        src/threading/rwp/Resource.cpp
        include/tulz/threading/rwp/Resource.h
        include/tulz/threading/rwp/ReadLock.h
        include/tulz/threading/rwp/WriteLock.h)

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

# https://learn.microsoft.com/en-us/cpp/cpp/dllexport-dllimport
# https://learn.microsoft.com/en-us/cpp/cpp/using-dllimport-and-dllexport-in-cpp-classes
if (WIN32)
    target_compile_definitions(tulz PUBLIC TULZ_BUILD_DLL)
endif()

if (UNIX AND NOT ANDROID)
    set(LINK_LIBRARIES ${LINK_LIBRARIES} pthread)
endif()

if (ANDROID)
    set(LINK_LIBRARIES ${LINK_LIBRARIES} android)
endif()

target_link_libraries(tulz ${LINK_LIBRARIES})

add_executable(tulz-examples examples/example.cpp)
target_link_libraries(tulz-examples tulz)

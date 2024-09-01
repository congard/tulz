cmake_minimum_required(VERSION 3.10)
project(tulz)

set(CMAKE_CXX_STANDARD 20)

set(TULZ_OBSERVER_SOURCES
        include/tulz/observer/Observer.h
        include/tulz/observer/Subject.h
        include/tulz/observer/Subscription.h
        include/tulz/observer/Observable.h
        include/tulz/observer/ObservableNumber.h
        include/tulz/observer/USubscription.h
        src/observer/routing/RoutingKey.cpp
        include/tulz/observer/routing/RoutingKey.h
        src/observer/routing/RoutingLevelView.cpp
        include/tulz/observer/routing/RoutingLevelView.h
        src/observer/routing/RoutingKeyBuilder.cpp
        include/tulz/observer/routing/RoutingKeyBuilder.h
        include/tulz/observer/routing/RoutingKeyLevel.h
        src/observer/routing/SubjectRouter.cpp
        include/tulz/observer/routing/SubjectRouter.h
        include/tulz/observer/routing/ConcurrentSubjectRouter.h
        include/tulz/observer/ObserverAutoPtr.h
        include/tulz/observer/EternalObserver.h
        include/tulz/observer/detail/ObserverFactory.h
        include/tulz/observer/EternalObserverFactory.h)

set(TULZ_THREADING_SOURCES
        include/tulz/threading/Runnable.h
        src/threading/Runnable.cpp
        include/tulz/threading/Thread.h
        src/threading/Thread.cpp
        include/tulz/threading/ThreadPool.h
        src/threading/ThreadPool.cpp
        src/threading/rwp/Resource.cpp
        include/tulz/threading/rwp/Resource.h
        include/tulz/threading/rwp/ReadLock.h
        include/tulz/threading/rwp/WriteLock.h)

set(TULZ_CONTAINER_SOURCES
        include/tulz/container/Array.h
        include/tulz/container/RingBuffer.h
        include/tulz/container/RandomAccessIndexIterator.h)

set(TULZ_DLL_SOURCES
        include/tulz/DynamicLibrary.h src/DynamicLibrary.cpp)

set(TULZ_UTIL_SOURCES
        include/tulz/util/macros.h
        include/tulz/util/static_initializer.h
        include/tulz/util/noncopyable.h
        include/tulz/util/nonmovable.h)

set(TULZ_GENERAL_SOURCES
        include/tulz/Path.h src/Path.cpp
        include/tulz/File.h src/File.cpp
        include/tulz/Exception.h src/Exception.cpp
        include/tulz/DirectoryVisitor.h src/DirectoryVisitor.cpp
        src/LocaleInfo.cpp include/tulz/LocaleInfo.h
        include/tulz/demangler.h
        src/demangler.cpp
        include/tulz/export.h)

if (ANDROID)
    set(TULZ_ANDROID_SOURCES
            android/src/assets/AssetManager.cpp android/include/tulz/assets/AssetManager.h
            android/src/assets/Asset.cpp android/include/tulz/assets/Asset.h
            android/src/assets/AssetDir.cpp android/include/tulz/assets/AssetDir.h)
endif()

add_library(tulz
        ${TULZ_OBSERVER_SOURCES}
        ${TULZ_THREADING_SOURCES}
        ${TULZ_CONTAINER_SOURCES}
        ${TULZ_DLL_SOURCES}
        ${TULZ_UTIL_SOURCES}
        ${TULZ_GENERAL_SOURCES}
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

target_link_libraries(tulz PUBLIC ${LINK_LIBRARIES})
target_include_directories(tulz PUBLIC include)

if (ANDROID)
    target_include_directories(tulz PUBLIC android/include)
endif()
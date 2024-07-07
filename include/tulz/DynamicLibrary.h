#ifndef TULZ_DYNAMICLIBRARY_H
#define TULZ_DYNAMICLIBRARY_H

#include <string>
#include <string_view>

namespace tulz {
class DynamicLibrary {
public:
    struct Error {
        bool error;
        std::string message;
    };

public:
    DynamicLibrary();
    explicit DynamicLibrary(std::string_view path);
    ~DynamicLibrary();

    void load(std::string_view path);
    void close();

    bool isLoaded() const;

    void* getAddress(std::string_view name);

    template<typename T>
    T getAddress(const std::string &name) {
        return reinterpret_cast<T>(getAddress(name));
    auto getAddress(std::string_view name) {
    }

    static Error getError();

private:
    void *m_lib = nullptr;
};
}

#endif //TULZ_DYNAMICLIBRARY_H

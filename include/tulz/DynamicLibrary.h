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

    /**
     * Returns function pointer casted to `F*`.
     * @tparam F The function signature, e.g. `void()`.
     * @param name The function name.
     * @return The function pointer if it was found, `nullptr` otherwise.
     */
    template<typename F>
    auto getAddress(std::string_view name) {
        return reinterpret_cast<F*>(getAddress(name));
    }

    static Error getError();

private:
    void *m_lib = nullptr;
};
}

#endif //TULZ_DYNAMICLIBRARY_H

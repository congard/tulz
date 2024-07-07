#include <tulz/DynamicLibrary.h>

#ifdef _WIN32
    #include <Windows.h>

    inline auto loadLibrary(const char *path) {
        SetLastError(0);
        return LoadLibrary(path);
    }

    #define closeLibrary(lib) FreeLibrary(reinterpret_cast<HINSTANCE>(lib))
    #define getAddr(lib, name) reinterpret_cast<void *>(GetProcAddress(reinterpret_cast<HINSTANCE>(lib), name))
#else
    #include <dlfcn.h>

    #define loadLibrary(path) dlopen(path, RTLD_LAZY)
    #define closeLibrary(lib) dlclose(lib)
    #define getAddr(lib, name) dlsym(lib, name)
#endif

namespace tulz {
DynamicLibrary::DynamicLibrary() = default;

DynamicLibrary::DynamicLibrary(std::string_view path) {
    load(path);
}

DynamicLibrary::~DynamicLibrary() {
    close();
}

void DynamicLibrary::load(std::string_view path) {
    if (isLoaded()) {
        close();
    }

    m_lib = loadLibrary(path.data());
}

void DynamicLibrary::close() {
    if (isLoaded()) {
        closeLibrary(m_lib);
    }

    m_lib = nullptr;
}

bool DynamicLibrary::isLoaded() const {
    return m_lib != nullptr;
}

void* DynamicLibrary::getAddress(std::string_view name) {
    return getAddr(m_lib, name.data());
}

DynamicLibrary::Error DynamicLibrary::getError() {
    Error error;
    error.error = false;

#ifdef _WIN32
    auto lastError = GetLastError();

    if (lastError != 0) {
        error.error = true;
        error.message = std::to_string(lastError);
    }

    SetLastError(0);
#else
    auto dlError = dlerror();

    if (dlError != nullptr) {
        error.error = true;
        error.message = dlError;
    }
#endif

    return error;
}
}

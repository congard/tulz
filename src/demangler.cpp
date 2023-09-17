#include <tulz/demangler.h>

#ifdef _WIN32
#include <windows.h>
#include <dbghelp.h>

#include <stdexcept>
#include <mutex>

#pragma comment(lib, "dbghelp.lib")

namespace tulz::demangler {
std::string demangle(std::string_view mangledName) {
    // UnDecorateSymbolName is not thread-safe:
    // https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-undecoratesymbolname
    // Hence, we need to perform some synchronization.
    auto safeUnDecorateSymbolName = [=](PSTR outputString, DWORD maxStringLength) {
#ifndef TULZ_DEMANGLER_DISABLE_THREAD_SAFETY
        static std::mutex mutex;
        std::scoped_lock lock(mutex);
#endif
        return UnDecorateSymbolName(mangledName.data(), outputString, maxStringLength, UNDNAME_COMPLETE);
    };

    if (char output[1024]; safeUnDecorateSymbolName(output, sizeof(output))) {
        constexpr const char *keywords[] = {"class", "struct", "enum"};

        std::string result {output};

        // remove keywords from the result
        for (auto keyword : keywords) {
            auto keywordLen = strlen(keyword);

            size_t pos = result.find(keyword);

            while (pos != std::string::npos) {
                auto isSeparator = [](auto c) {
                    return !std::isalnum(c) && c != '_';
                };

                bool isErase =
                    // check if keyword is not a right part of the name
                    (pos == 0 || isSeparator(result.at(pos - 1))) &&

                    // check if keyword is not a left part of the name
                    (pos + keywordLen < result.size() && isSeparator(result.at(pos + keywordLen)));

                if (isErase) {
                    if (pos > 0 && result.at(pos - 1) == ',') {
                        // preserve space
                        result.erase(pos, keywordLen);
                    } else {
                        // +1 for space
                        result.erase(pos, keywordLen + 1);
                    }

                    pos = result.find(keyword, pos);
                } else {
                    pos = result.find(keyword, pos + keywordLen);
                }
            }
        }

        return result;
    } else {
        DWORD error = GetLastError();
        throw std::runtime_error("UnDecorateSymbolName failed, error code " + std::to_string(error));
    }
}
}
#else
#include <cxxabi.h>

namespace tulz::demangler {
std::string demangle(std::string_view mangledName) {
    const auto dmg = abi::__cxa_demangle(mangledName.data(), nullptr, nullptr, nullptr);
    std::string name = dmg;
    std::free(dmg);
    return name;
}
}
#endif

#ifndef TULZ_DEMANGLER_H
#define TULZ_DEMANGLER_H

#include <string>
#include <string_view>

namespace tulz::demangler {
/**
 * Demangles the specified mangled name.
 * @param mangledName The mangled name returned by `typeid(T).name()`.
 * @return The demangled name.
 * @note On Windows, keywords will be removed, e.g.
 * `class Foo` -> `Foo`, `struct A\<class B\>` -> `A\<B\>`
 */
std::string demangle(std::string_view mangledName);
}

#endif //TULZ_DEMANGLER_H

#ifndef TULZ_STATIC_INITIALIZER_H
#define TULZ_STATIC_INITIALIZER_H

/**
 * This macro must be placed inside the class
 * where you want to add a static initializer
 */
#define STATIC_INITIALIZER_DECL \
private: \
    static struct _static_initializer_t { \
        _static_initializer_t(); \
    } _static_initializer;

/**
 * Static initializer definition.
 * @arg className the name of the class that has the static initializer
 */
#define STATIC_INITIALIZER_DEF(...) \
__VA_ARGS__::_static_initializer_t __VA_ARGS__::_static_initializer {};

/**
 * Static initializer definition + implementation.
 * Usage: place STATIC_INITIALIZER_IMPL(ClassName) { ... } in cpp file
 * @arg className the name of the class that has the static initializer
 */
#define STATIC_INITIALIZER_IMPL(...) \
STATIC_INITIALIZER_DEF(__VA_ARGS__) \
__VA_ARGS__::_static_initializer_t::_static_initializer_t()

/**
 * This macro must be placed inside the class where
 * you want to add an inline static initializer.
 * Note: inline static initializer doesn't require
 * STATIC_INITIALIZER_DEF
 */
#define INLINE_STATIC_INITIALIZER(...) \
private: \
    inline static struct _static_initializer_t { \
        _static_initializer_t() __VA_ARGS__ \
    } _static_initializer;

#endif //TULZ_STATIC_INITIALIZER_H

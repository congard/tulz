#ifndef TULZ_EXPORT_H
#define TULZ_EXPORT_H

#if !__linux__
#ifdef TULZ_BUILD_DLL
        #define TULZ_API __declspec(dllexport)
    #else
        #define TULZ_API __declspec(dllimport)
    #endif
#else
#define TULZ_API
#endif

#endif //TULZ_EXPORT_H

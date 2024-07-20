#ifndef TULZ_PATH_H
#define TULZ_PATH_H

#include <tulz/export.h>

#include <string>
#include <forward_list>

namespace tulz {
typedef unsigned char byte;

/**
 * The class provides basic functions for working with Path
 */
class TULZ_API Path {
public:
    enum Error {
        NotFile,
        NotDirectory,
        NotFound
    };

public:
    static constexpr char Separator = '/';

#ifdef __linux__
    static constexpr char SystemSeparator = '/';
#elif defined(_WIN32)
    static constexpr char SystemSeparator = '\\';
#endif

public:
    Path();
    explicit Path(const std::string &path);

    void setPath(const std::string &path);

    bool exists() const;
    bool isFile() const;
    bool isDirectory() const;
    bool isAbsolute() const;

    size_t size() const;

    const std::string& toString() const;
    std::string getPathName() const;
    Path getParentDirectory() const;

    std::forward_list<Path> listChildren() const;

    static void setWorkingDirectory(const Path &dir);
    static void setWorkingDirectory(const std::string &dir);

    static Path getWorkingDirectory();
    static Path getSystemPath();

    static Path join(const Path &p1, const Path &p2);
    static std::string join(const std::string &p1, const std::string &p2);

    template<typename ...Args>
    static Path join(const Path &p1, const Path &p2, const Args& ...args) {
        return join(join(p1, p2), args...);
    }

    template<typename ...Args>
    static std::string join(const std::string &p1, const std::string &p2, const Args& ...args) {
        return join(join(p1, p2), args...);
    }

protected:
    std::string m_path;
};

inline Path operator"" _p(const char* str, size_t len) {
    return Path(std::string(str, len));
}
}

#endif //TULZ_PATH_H

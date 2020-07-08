#ifndef TULZ_PATH_H
#define TULZ_PATH_H

#include <string>
#include <tulz/Array.h>
#include <vector>

namespace tulz {
typedef unsigned char byte;

/**
 * The class provides basic functions for working with Path
 */
class Path {
public:
    enum Error {
        NotFile,
        NotDirectory,
        NotFound
    };

    static constexpr char Separator = '/';
#ifdef __linux__
    static constexpr char SystemSeparator = '/';
#elif defined(__MINGW32__)
    static constexpr char SystemSeparator = '\\';
#endif

    Path() = default;
    explicit Path(const std::string &path);

    void setPath(const std::string &path);

    bool exists();
    bool isFile();
    bool isDirectory();
    bool isAbsolute();

    size_t size();

    std::string toString();
    std::string getParentDirectory();
    std::string getPathName();

    std::vector<std::string> listChilds();

    static std::string getWorkingDirectory();
    static std::string join(const std::string &p1, const std::string &p2);

protected:
    std::string path;
};
}

#endif //TULZ_PATH_H

#include <tulz/Path.h>

#include <tulz/StringUtils.h>
#include <tulz/Exception.h>

#include <cstring>

#ifdef __linux__
    #include <dirent.h>
    #include <unistd.h>

    #define setCurrentDir chdir
    #define getCurrentDir getcwd
#elif defined(_WIN32)
    #include <Windows.h>

    #define setCurrentDir SetCurrentDirectory
    #define getCurrentDir(buffer, length) GetCurrentDirectory(length, buffer)
#endif

using namespace std;

namespace tulz {
Path::Path() = default;

Path::Path(const string &path) {
    setPath(path);
}

void Path::setPath(const string &path) {
    m_path = path;

    StringUtils::replaceAll(m_path, "\\", "/");

    if (m_path.back() == Separator) {
        m_path.erase(m_path.length() - 1, 1);
    }
}

bool Path::exists() const {
#if defined(__linux__)
    FILE *file = fopen(m_path.c_str(), "r");

    if (file) {
        fclose(file);
    }

    return file;
#elif defined(_WIN32)
    return GetFileAttributes(m_path.c_str()) != INVALID_FILE_ATTRIBUTES;
#endif
}

bool Path::isFile() const {
#if defined(__linux__)
    return exists() && !isDirectory();
#elif defined(_WIN32)
    auto attributes = GetFileAttributes(m_path.c_str());

    return (attributes != INVALID_FILE_ATTRIBUTES) && !(attributes & FILE_ATTRIBUTE_DIRECTORY);
#endif
}

bool Path::isDirectory() const {
#if defined(__linux__)
    auto dir = opendir(m_path.c_str());

    if (dir) {
        closedir(dir);
    }

    return dir;
#elif defined(_WIN32)
    auto attributes = GetFileAttributes(m_path.c_str());

    return (attributes != INVALID_FILE_ATTRIBUTES) && (attributes & FILE_ATTRIBUTE_DIRECTORY);
#endif
}

inline bool isAbsolutePath(const string &path) {
#ifdef __linux__
    return path.find(Path::Separator) == 0; // /home/folder
#elif defined(_WIN32)
    return path.find(':') == 1; // C:/folder
#endif
}

bool Path::isAbsolute() const {
    return isAbsolutePath(m_path);
}

#define checkExistence() \
if (!exists()) \
    throw Exception(m_path + " not found", NotFound);

size_t Path::size() const {
    checkExistence()

    if (isFile()) {
        FILE *file = fopen(m_path.c_str(), "rb");

        fseek(file, 0, SEEK_END);

        size_t size = ftell(file);

        fclose(file);

        return size;
    } else {
        auto children = listChildren();
        size_t size = 0;

        for (const auto &child : children) {
            size += Path::join(*this, child).size();
        }

        return size;
    }
}

const string& Path::toString() const {
    return m_path;
}

Path Path::getParentDirectory() const {
    string path = m_path;

    size_t separatorPos = path.find_last_of("/\\");

    // remove last separator if exists
    // if path.size() == 0, then path.size() - 1 == string::npos
    if (separatorPos != string::npos && separatorPos == path.size() - 1) {
        path.erase(separatorPos, path.size());
        separatorPos = path.find_last_of("/\\");
    }

    // 'dir' or '/', 'D:/' etc
    if (separatorPos == string::npos)
        return {}; // means 'already here, no parent directory'

    return Path(path.erase(separatorPos, m_path.size()));
}

string Path::getPathName() const {
    return string(m_path).erase(0, m_path.find_last_of("/\\") + 1);
}

forward_list<Path> Path::listChildren() const {
    checkExistence()

    forward_list<Path> result;

#if defined(__linux__)
    DIR *dir = opendir(m_path.c_str());

    if (dir == nullptr) {
        throw Exception(m_path + " is not directory", NotDirectory);
    }

    dirent *ent;

    while ((ent = readdir(dir)) != nullptr) {
        auto name = ent->d_name;

        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
            continue;
        }

        result.emplace_front(name);
    }

    closedir(dir);
#elif defined(_WIN32) // TODO: check for '.' and '..'
    string pattern(m_path);
    pattern.append("\\*");

    WIN32_FIND_DATA data;
    HANDLE hFind;

    if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
        do {
            result.emplace_front(data.cFileName);
        } while (FindNextFile(hFind, &data) != 0);

        FindClose(hFind);
    }
#endif

    return result;
}

void Path::setWorkingDirectory(const Path &dir) {
    setWorkingDirectory(dir.toString());
}

void Path::setWorkingDirectory(const string &dir) {
    setCurrentDir(dir.c_str());
}

Path Path::getWorkingDirectory() {
    char buff[FILENAME_MAX];

    getCurrentDir(buff, FILENAME_MAX);

    return Path(buff);
}

Path Path::join(const Path &p1, const Path &p2) {
    return Path(join(p1.toString(), p2.toString()));
}

string Path::join(const string &p1, const string &p2) {
    if (p1.empty())
        return p2;

    // if p2 is absolute just return it
    if (isAbsolutePath(p2))
        return p2;

    if (p1.back() != Separator && p1.back() != SystemSeparator)
        return p1 + SystemSeparator + p2;

    return p1 + p2;
}
}
#include <tulz/path.h>
#include <tulz/StringUtils>
#include <tulz/Exception>
#include <dirent.h>
#include <unistd.h>

#ifdef __linux__
#define _getCurrentDir getcwd
#elif __MINGW32__
#define _getCurrentDir _getcwd
#endif

namespace tulz {
Path::Path(const std::string &path) {
    setPath(path);
}

void Path::setPath(const std::string &_path) {
    this->path = _path;
    StringUtils::replaceAll(path, "\\", "/");
    if (path.back() == Separator)
        path.erase(path.length() - 1, 1);
}

bool Path::exists() {
    FILE *file = fopen(path.c_str(), "r");
    if (file)
        fclose(file);
    return file;
}

bool Path::isFile() {
    return exists() && !isDirectory();
}

bool Path::isDirectory() {
    DIR *dir = opendir(path.c_str());
    if (dir)
        closedir(dir);
    return dir;
}

bool Path::isAbsolute() {
#ifdef __linux__
    return path.find(Separator) == 0; // /home/folder
#elif defined(__MINGW32__)
    return path.find(Separator) == 2; // C:/folder
#endif
}

#define _checkExists \
if (!exists()) \
    throw Exception(path + " not found", NotFound);

size_t Path::size() {
    _checkExists

    if (isFile()) {
        FILE *file = fopen(path.c_str(), "rb");
        fseek(file, 0, SEEK_END);
        size_t size = ftell(file);
        fclose(file);
        return size;
    } else {
        std::vector<std::string> items = listChilds();
        size_t size = 0;
        for (const auto & item : items) {
            if (item == "." || item == "..")
                continue;
            size += Path(Path::join(path, item)).size();
        }

        return size;
    }
}

std::string Path::toString() {
    return path;
}

std::string Path::getParentDirectory() {
    size_t separatorPos = path.find_last_of(Separator);
    // 'dir' or '/', 'D:/' etc
    if (separatorPos == std::string::npos || separatorPos == path.find_first_of(Separator))
        return path;
    return std::string(path).erase(separatorPos, path.size());
}

std::string Path::getPathName() {
    return std::string(path).erase(0, path.find_last_of(Path::Separator) + 1);
}

std::vector<std::string> Path::listChilds() {
    _checkExists

    std::vector<std::string> result;
    DIR *dir = opendir(path.c_str());

    if (!dir)
        throw Exception(path + " is not directory", NotDirectory);

    dirent *ent;
    while ((ent = readdir (dir)) != nullptr)
        result.emplace_back(ent->d_name);
    closedir (dir);

    return result;
}

std::string Path::getWorkingDirectory() {
    char buff[FILENAME_MAX];
    _getCurrentDir(buff, FILENAME_MAX);
    return std::string(buff);
}

std::string Path::join(const std::string &p1, const std::string &p2) {
    std::string first = p1;
    std::string second = p2;

    if (first.back() != Separator)
        first += Separator;

    if (second.front() == Separator)
        second.erase(0, 1);

    return first + second;
}
}
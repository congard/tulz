#include <tulz/Path.h>
#include <tulz/StringUtils.h>
#include <tulz/Exception.h>
#include <dirent.h>
#include <unistd.h>

#ifdef __linux__
#define _getCurrentDir getcwd
#elif __MINGW32__
#define _getCurrentDir _getcwd
#endif

using namespace std;

namespace tulz {
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

bool Path::exists() {
    FILE *file = fopen(m_path.c_str(), "r");

    if (file)
        fclose(file);

    return file;
}

bool Path::isFile() {
    return exists() && !isDirectory();
}

bool Path::isDirectory() {
    DIR *dir = opendir(m_path.c_str());

    if (dir)
        closedir(dir);

    return dir;
}

bool Path::isAbsolute() {
#ifdef __linux__
    return m_path.find(Separator) == 0; // /home/folder
#elif defined(__MINGW32__)
    return path.find(Separator) == 2; // C:/folder
#endif
}

#define checkExistence() \
if (!exists()) \
    throw Exception(m_path + " not found", NotFound);

size_t Path::size() {
    checkExistence()

    if (isFile()) {
        FILE *file = fopen(m_path.c_str(), "rb");
        fseek(file, 0, SEEK_END);
        size_t size = ftell(file);
        fclose(file);

        return size;
    } else {
        vector<string> items = listChilds();
        size_t size = 0;

        for (const auto & item : items) {
            if (item == "." || item == "..")
                continue;

            size += Path(Path::join(m_path, item)).size();
        }

        return size;
    }
}

string Path::toString() {
    return m_path;
}

string Path::getParentDirectory() {
    size_t separatorPos = m_path.find_last_of(Separator);

    // 'dir' or '/', 'D:/' etc
    if (separatorPos == string::npos || separatorPos == m_path.find_first_of(Separator))
        return m_path;

    return string(m_path).erase(separatorPos, m_path.size());
}

string Path::getPathName() {
    return string(m_path).erase(0, m_path.find_last_of(Path::Separator) + 1);
}

vector<string> Path::listChilds() {
    checkExistence()

    vector<string> result;
    DIR *dir = opendir(m_path.c_str());

    if (!dir)
        throw Exception(m_path + " is not directory", NotDirectory);

    dirent *ent;

    while ((ent = readdir (dir)) != nullptr)
        result.emplace_back(ent->d_name);

    closedir(dir);

    return result;
}

void Path::setWorkingDirectory(const string &dir) {
    chdir(dir.c_str());
}

string Path::getWorkingDirectory() {
    char buff[FILENAME_MAX];
    _getCurrentDir(buff, FILENAME_MAX);

    return string(buff);
}

string Path::join(const string &p1, const string &p2) {
    string first = p1;
    string second = p2;

    if (first.back() != Separator)
        first += Separator;

    if (second.front() == Separator)
        second.erase(0, 1);

    return first + second;
}
}
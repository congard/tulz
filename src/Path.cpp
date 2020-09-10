#include <tulz/Path.h>
#include <tulz/StringUtils.h>
#include <tulz/Exception.h>
#include <dirent.h>
#include <unistd.h>

#ifdef __linux__
#define getCurrentDir getcwd
#elif __MINGW32__
#define getCurrentDir _getcwd
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
        return ""; // means 'already here'

    return path.erase(separatorPos, m_path.size());
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

    while ((ent = readdir(dir)) != nullptr)
        result.emplace_back(ent->d_name);

    closedir(dir);

    return result;
}

void Path::setWorkingDirectory(const string &dir) {
    chdir(dir.c_str());
}

string Path::getWorkingDirectory() {
    char buff[FILENAME_MAX];
    getCurrentDir(buff, FILENAME_MAX);

    return string(buff);
}

string Path::join(const string &p1, const string &p2) {
    if (p1.empty())
        return p2;

    // if p2 is absolute just return it
    if (p2.front() == Separator)
        return p2;

    if (p1.back() != Separator && p1.back() != SystemSeparator)
        return p1 + SystemSeparator + p2;

    return p1 + p2;
}
}
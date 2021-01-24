#include <tulz/Path.h>
#include <tulz/File.h>

#include <tulz/StringUtils.h>

#include <iostream>

using namespace tulz;
using namespace std;

void filesystem() {
    cout << "=== filesystem ===\n\n";

    auto workingDirectory = Path::getWorkingDirectory();
    auto newWorkingDirectory = workingDirectory;

    while (newWorkingDirectory.getPathName() != "tulz") {
        newWorkingDirectory = newWorkingDirectory.getParentDirectory();
    }

    cout << "Working directory: " << workingDirectory.toString() << "\n";
    cout << "Setting working directory to " << newWorkingDirectory.toString() << "\n";

    Path::setWorkingDirectory(newWorkingDirectory);

    workingDirectory = Path::getWorkingDirectory();

    cout << "Working directory: " << workingDirectory.toString() << "\n";

    cout << "\nThis directory contains next files and directories:\n";

    for (const auto &s : workingDirectory.listChildren()) {
        cout << s.toString() << "\n";
    }

    // bool to string
    auto b2s = [](bool b) {
        return b ? "true" : "false";
    };

    auto filePath = Path(Path::join(workingDirectory.toString(), "examples", "directory", "hello.txt"));

    cout << "\nFile " << filePath.toString() << "\n";
    cout << "exists: " << b2s(filePath.exists()) << "\n";
    cout << "file: " << b2s(filePath.isFile()) << "\n";
    cout << "directory: " << b2s(filePath.isDirectory()) << "\n";
    cout << "absolute path: " << b2s(filePath.isAbsolute()) << "\n";
    cout << "size: " << filePath.size() << "\n";
    cout << "content: " + File(filePath, File::Mode::ReadText).readStr() << "\n";
}

void regex() {
    cout << "\n=== regex ===\n\n";

    string src = "apple pineapple tomato potato";
    string regex = "[a-z]+o";

    cout << "src: " << src << "\n";
    cout << "regex: " << regex << "\n";
    cout << "matches:\n";

    auto matches = StringUtils::findRegex(src, regex);

    for (const auto &m : matches) {
        for (const auto &match : m.matches) {
            cout << match << "\n";
        }
    }
}

int main() {
    filesystem();
    regex();

    return 0;
}

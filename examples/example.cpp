#include <tulz/Path.h>
#include <tulz/File.h>

#include <tulz/StringUtils.h>

#include <tulz/threading/Thread.h>
#include <tulz/threading/ThreadPool.h>
#include <tulz/threading/MutexLocker.h>

#include <iostream>
#include <utility>

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

void threading() {
    cout << "\n=== threading ===\n\n";

    class MyRunnable: public Runnable {
    public:
        explicit MyRunnable(string name)
            : name(std::move(name)) {}

        ~MyRunnable() override {
            cout << "~MyRunnable (" << name << ")\n";
        }

        void run() override {
            cout << "MyRunnable output begins (" << name << ")\n";
            Thread::sleep(4s);
            cout << "MyRunnable output ends (" << name << ")\n";
        }

    private:
        string name;
    };

    ThreadPool pool;
    pool.setMaxThreadCount(2);
    pool.setExpiryTimeout(1000);

    pool.start([]() {
        cout << "Lambda 1 first message\n";
        Thread::sleep(2s);
        cout << "Lambda 1 last message\n";
    });

    pool.start([](const string &arg) {
        cout << "Lambda 2 first message\n";
        cout << "Lambda 2 arg is: '" << arg << "'\n";
        Thread::sleep(3s);
        cout << "Lambda 2 last message\n";
    }, "just a string argument");

    pool.start(new MyRunnable("foo"));
    pool.start(new MyRunnable("bar"));

    while (pool.getActiveThreadCount() > 0) {
        pool.update();
        Thread::sleep(500);
    }

    cout << "There are no active threads left in the pool\n";

    pool.stop();
}

int main() {
    filesystem();
    regex();
    threading();

    return 0;
}

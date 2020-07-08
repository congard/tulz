# Tulz
Tulz is cross-platform tools library for C++ development

# Installing
1. Put sources in your libs folder
2. Add tulz to your project `add_subdirectory(your_libs_folder/tulz)`
3. After `add_executable(your_project ...)` add `target_link_libraries(your_project tulz)`

# Usage
```cpp
#include <iostream>
#include <tulz/File.h>
#include <tulz/Path.h>
#include <tulz/Exception.h>
#include <tulz/StringUtils.h>

using namespace tulz;

int main() {
    try {
        std::string fileLocation = "/home/congard/wx.cpp";
        Path path(fileLocation);
        std::cout << "Exists: " << path.exists()
                  << "\nIs file: " << path.isFile()
                  << "\nParent directory: " << path.getParentDirectory()
                  << "\nPath name: " << path.getPathName()
                  << "\n\n";

        File file(fileLocation, File::ReadText);
        std::cout << "File size is: " << file.size() << " bytes\nData:\n" << file.readStr();
        file.close();
    } catch (const Exception &exception) {
        std::cout << exception.message << "\n";
    }

    std::string text = "apple pineapple tomato potato";
    std::string regex = "[pt][a-z]+o";
    auto matches = StringUtils::findRegex(text, regex);
    for (const auto & m : matches) {
        for (const auto & match : m.matches)
            std::cout << match << "\n";
    }
    return 0;
}
```

# Donate
<b>Payeer:</b> P36281059

Or you can do it even without finance. Just open [this](http://fainbory.com/8aWY) link

Thank you.
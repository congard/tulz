#ifndef TULZ_ASSETDIR_H
#define TULZ_ASSETDIR_H

#include <forward_list>
#include <string>

struct AAssetDir;

namespace tulz {
class AssetDir {
public:
    explicit AssetDir(const std::string &path);
    AssetDir();
    AssetDir(AssetDir &&src) noexcept;
    AssetDir& operator=(AssetDir &&rhs) noexcept;

    ~AssetDir();

    void open(const std::string &path);
    void close();
    void rewind();

    bool isOpen() const;

    const char* getNextFileName() const;
    std::forward_list<std::string> listFiles();

private:
    AssetDir(const AssetDir &src);
    AssetDir& operator=(const AssetDir &rhs);

private:
    AAssetDir* m_javaAssetDir {nullptr};
};
}

#endif //TULZ_ASSETDIR_H

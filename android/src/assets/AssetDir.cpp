#include <tulz/assets/AssetDir.h>
#include <tulz/assets/AssetManager.h>

#include <android/asset_manager.h>

namespace tulz {
AssetDir::AssetDir(const std::string &path) {
    open(path);
}

AssetDir::AssetDir() = default;

AssetDir::AssetDir(AssetDir &&src) noexcept {
    std::swap(m_javaAssetDir, src.m_javaAssetDir);
}

AssetDir& AssetDir::operator=(AssetDir &&rhs) noexcept {
    std::swap(m_javaAssetDir, rhs.m_javaAssetDir);
    return *this;
}

AssetDir::~AssetDir() {
    close();
}

void AssetDir::open(const std::string &path) {
    m_javaAssetDir = AAssetManager_openDir(AssetManager::getJavaAssetManager(), path.c_str());
}

void AssetDir::close() {
    if (m_javaAssetDir) {
        AAssetDir_close(m_javaAssetDir);
        m_javaAssetDir = nullptr;
    }
}

void AssetDir::rewind() {
    AAssetDir_rewind(m_javaAssetDir);
}

bool AssetDir::isOpen() const {
    return m_javaAssetDir;
}

const char* AssetDir::getNextFileName() const {
    return AAssetDir_getNextFileName(m_javaAssetDir);
}

std::forward_list<std::string> AssetDir::listFiles() {
    rewind();

    std::forward_list<std::string> list;
    const char* name;

    while ((name = getNextFileName()) != nullptr) {
        list.emplace_front(name);
    }

    rewind();

    return list;
}

AssetDir::AssetDir(const AssetDir &src) = default;

AssetDir& AssetDir::operator=(const AssetDir &rhs) = default;
}

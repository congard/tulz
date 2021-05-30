#include <tulz/assets/AssetManager.h>

namespace tulz {
AAssetManager* AssetManager::m_javaAssetManager;

Asset AssetManager::openFile(const std::string &path, Asset::Mode mode) {
    return Asset {path, mode};
}

AssetDir AssetManager::openDirectory(const std::string &path) {
    return AssetDir {path};
}

bool AssetManager::isFile(const std::string &path) {
    return Asset(path).isOpen();
}

bool AssetManager::isDirectory(const std::string &path) {
    return AssetDir(path).getNextFileName();
}

bool AssetManager::exists(const std::string &path) {
    return isFile(path) || isDirectory(path);
}

void AssetManager::setJavaAssetManager(AAssetManager *manager) {
    m_javaAssetManager = manager;
}

AAssetManager* AssetManager::getJavaAssetManager() {
    return m_javaAssetManager;
}
}

#ifndef TULZ_ASSETMANAGER_H
#define TULZ_ASSETMANAGER_H

#include <string>

#include "Asset.h"
#include "AssetDir.h"

struct AAssetManager;

namespace tulz {
/**
 * You must call <b>setJavaAssetManager</b> manually before using assets!
 */
class AssetManager {
public:
    static Asset openFile(const std::string &path, Asset::Mode mode = Asset::Mode::Unknown);
    static AssetDir openDirectory(const std::string &path);

    static bool isFile(const std::string &path);
    static bool isDirectory(const std::string &path);
    static bool exists(const std::string &path);

    static void setJavaAssetManager(AAssetManager *manager);
    static AAssetManager* getJavaAssetManager();

private:
    static AAssetManager* m_javaAssetManager;
};
}

#endif //TULZ_ASSETMANAGER_H

#include <tulz/assets/Asset.h>
#include <tulz/assets/AssetManager.h>

#include <android/asset_manager.h>

namespace tulz {
Asset::Asset(const std::string &path, Asset::Mode mode) {
    open(path, mode);
}

Asset::Asset() = default;

Asset::Asset(Asset &&src) noexcept {
    std::swap(m_javaAsset, src.m_javaAsset);
}

Asset& Asset::operator=(Asset &&rhs) noexcept {
    std::swap(m_javaAsset, rhs.m_javaAsset);
    return *this;
}

Asset::~Asset() {
    close();
}

void Asset::open(const std::string &path, Asset::Mode mode) {
    m_javaAsset = AAssetManager_open(AssetManager::getJavaAssetManager(), path.c_str(), static_cast<int>(mode));
}

void Asset::close() {
    if (m_javaAsset) {
        AAsset_close(m_javaAsset);
        m_javaAsset = nullptr;
    }
}

void Asset::read(void *buffer, size_t count) const {
    AAsset_read(m_javaAsset, buffer, count);
}

void Asset::seek32(off_t offset, int whence) {
    AAsset_seek(m_javaAsset, offset, whence);
}

void Asset::seek(off64_t offset, int whence) {
    AAsset_seek64(m_javaAsset, offset, whence);
}

off_t Asset::tell32() const {
    return getLength32() - getRemainingLength32();
}

off64_t Asset::tell() const {
    return getLength() - getRemainingLength();
}

bool Asset::isOpen() const {
    return m_javaAsset;
}

const void* Asset::getBuffer() const {
    return AAsset_getBuffer(m_javaAsset);
}

std::string Asset::getString() const {
    return std::string(static_cast<const char*>(getBuffer()), getLength());
}

off_t Asset::getLength32() const {
    return AAsset_getLength(m_javaAsset);
}

off64_t Asset::getLength() const {
    return AAsset_getLength64(m_javaAsset);
}

off_t Asset::getRemainingLength32() const {
    return AAsset_getRemainingLength(m_javaAsset);
}

off64_t Asset::getRemainingLength() const {
    return AAsset_getRemainingLength64(m_javaAsset);
}

Asset::Asset(const Asset &src) = default;

Asset& Asset::operator=(const Asset &rhs) = default;
}

#ifndef TULZ_ASSET_H
#define TULZ_ASSET_H

#include <string>

struct AAsset;

namespace tulz {
class Asset {
public:
    enum class Mode {
        Unknown = 0,
        Random = 1,
        Streaming = 2,
        Buffer = 3
    };

public:
    explicit Asset(const std::string &path, Mode mode = Mode::Unknown);
    Asset();
    Asset(Asset &&src) noexcept;
    Asset& operator=(Asset &&rhs) noexcept;

    ~Asset();

    void open(const std::string &path, Mode mode);
    void close();

    int read(void *buffer, size_t count) const;
    off_t seek32(off_t offset, int whence);
    off64_t seek(off64_t offset, int whence);

    off_t tell32() const;
    off64_t tell() const;

    bool isOpen() const;

    const void* getBuffer() const;
    std::string getString() const;
    off_t getLength32() const;
    off64_t getLength() const;
    off_t getRemainingLength32() const;
    off64_t getRemainingLength() const;

private:
    Asset(const Asset &src);
    Asset& operator=(const Asset &rhs);

private:
    AAsset* m_javaAsset {nullptr};
};
}

#endif //TULZ_ASSET_H

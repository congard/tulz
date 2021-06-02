#ifndef TULZ_FILE_H
#define TULZ_FILE_H

#include <tulz/Path.h>

namespace tulz {

/**
 * C++ implementation of C FILE
 */
class File {
public:
    enum class Mode {
        None,
        ReadText,
        Read,
        WriteText,
        Write,
        AppendText,
        Append
    };

    enum class Origin {
        Start = SEEK_SET,
        Current = SEEK_CUR,
        End = SEEK_END
    };

public:
    File(const Path &path, Mode mode);
    File(const std::string &path, Mode mode);
    File();
    ~File();

    void open(const Path &path, Mode mode);
    void close();

    int flush();

    size_t write(const void *data, size_t size, size_t elementSize = 1);
    size_t write(const Array<byte> &data);
    size_t write(const std::string &str);

    size_t read(void *buffer, size_t size, size_t count = 1) const;
    Array<byte> read();
    std::string readStr();

    int seek(long offset, Origin origin);

    bool isOpen() const;
    long tell() const;
    size_t size() const;
    Mode getMode() const;

private:
    FILE *m_file;
    Mode m_mode;
};
}

#endif //TULZ_FILE_H

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

public:
    File(const std::string &path, Mode mode);
    File();
    ~File();

    void open(const std::string &path, Mode mode);
    void close();

    void write(const void *data, size_t size, size_t elementSize = 1);
    void write(const Array<byte> &data);
    void write(const std::string &str);

    Array<byte> read();
    std::string readStr();

    bool isOpen() const;
    size_t size();
    Mode getMode() const;

private:
    FILE *m_file;
    Mode m_mode;
};
}

#endif //TULZ_FILE_H

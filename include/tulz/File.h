#ifndef TULZ_FILE_H
#define TULZ_FILE_H

#include <tulz/Path.h>

namespace tulz {

/**
 * C++ implementation of C FILE
 */
class File {
public:
#define constant(name, data) static constexpr char name[] = data;
    constant(ReadText, "r")
    constant(Read, "rb")
    constant(WriteText, "w")
    constant(Write, "wb")
    constant(AppendText, "a")
    constant(Append, "ab")
#undef constant

    File(const std::string &path, const std::string &mode);
    File();
    ~File();

    void open(const std::string &path, const std::string &mode);
    void close();

    void write(const void *data, size_t size, size_t elementSize = 1);
    void write(const Array<byte> &data);
    void write(const std::string &str);

    Array<byte> read();
    std::string readStr();

    bool isOpen();
    size_t size();

protected:
    FILE *file = nullptr;
};
}

#endif //TULZ_FILE_H

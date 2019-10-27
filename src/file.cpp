#include "tulz/file.h"

#include <iostream>
#include <tulz/Exception>

namespace tulz {

#define def_constant(name) constexpr char File::name[];
def_constant(ReadText)
def_constant(Read)
def_constant(WriteText)
def_constant(Write)
def_constant(AppendText)
def_constant(Append)
#undef def_constant

File::File(const std::string &path, const std::string &mode) {
    open(path, mode);
}

void File::open(const std::string &path, const std::string &mode) {
    Path p(path);
    if (!p.isFile()) {
        if (!p.exists())
            throw Exception("File " + path + " not found", Path::NotFound);
        throw Exception(path + " is not file, it is directory", Path::NotFile);
    }

    file = fopen(p.toString().c_str(), mode.c_str());
}

void File::close() {
    if (!file)
        std::cerr << "Can't close file: file not opened";
    else {
        fclose(file);
        file = nullptr;
    }
}

void File::write(const void *data, const size_t size, const size_t elementSize) {
    fwrite(data, elementSize, size, file);
}

void File::write(const Array<byte> &data) {
    write(data.array(), data.size());
}

void File::write(const std::string &string) {
    write(string.c_str(), string.length());
}

Array<byte> File::read() {
    size_t fsize = size();
    Array<byte> result(fsize);
    fread(result.m_array, 1, fsize, file);
    return result;
}

std::string File::readStr() {
    auto data = read();
    return std::string(reinterpret_cast<char const *>(data.array()), data.size());
}

size_t File::size() {
    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    return fsize;
}
}
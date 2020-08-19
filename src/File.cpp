#include "tulz/File.h"

#include <tulz/Exception.h>

#include <iostream>

using namespace std;

namespace tulz {

#define def_constant(name) constexpr char File::name[];
def_constant(ReadText)
def_constant(Read)
def_constant(WriteText)
def_constant(Write)
def_constant(AppendText)
def_constant(Append)
#undef def_constant

File::File(const string &path, const string &mode) {
    open(path, mode);
}

File::File() = default;

inline bool isWriteMode(const string &mode) {
    return mode == File::WriteText || mode == File::Write || mode == File::AppendText || mode == File::Append;
}

void File::open(const string &path, const string &mode) {
    Path p(path);

    if (!p.exists() && !isWriteMode(mode))
        throw Exception("File " + path + " not found", Path::NotFound);

    if (p.exists() && p.isDirectory())
        throw Exception(path + " is not file, it is directory", Path::NotFile);

    file = fopen(p.toString().c_str(), mode.c_str());
}

void File::close() {
    if (!file)
        cerr << "Can't close file: file not opened";
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

void File::write(const string &str) {
    write(str.c_str(), str.length());
}

Array<byte> File::read() {
    size_t fsize = size();

    Array<byte> result(fsize);
    fread(result.m_array, 1, fsize, file);

    return result;
}

string File::readStr() {
    auto data = read();
    return string(reinterpret_cast<char const *>(data.array()), data.size());
}

size_t File::size() {
    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    return fsize;
}
}
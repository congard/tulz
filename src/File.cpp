#include "tulz/File.h"

#include <tulz/Exception.h>

#include <iostream>

using namespace std;

namespace tulz {
File::File(const Path &path, Mode mode)
    : File()
{
    open(path, mode);
}

File::File(const string &path, Mode mode)
    : File(Path(path), mode) {}

File::File()
    : m_file(nullptr),
      m_mode(Mode::None) {}

File::~File() {
    if (isOpen()) {
        close();
    }
}

void File::open(const Path &path, Mode mode) {
    auto isWriteMode = [&]()
    {
        return mode == Mode::WriteText || mode == Mode::Write || mode == Mode::AppendText || mode == Mode::Append;
    };

    auto getModeStr = [&]()
    {
        switch (mode) {
            case Mode::ReadText: return "r";
            case Mode::Read: return "rb";
            case Mode::WriteText: return "w";
            case Mode::Write: return "wb";
            case Mode::AppendText: return "a";
            case Mode::Append: return "ab";
            case Mode::None: throw invalid_argument("Invalid mode value: None");
            default: throw invalid_argument("Invalid mode value");
        }
    };

    const auto &pathStr = path.toString();

    if (!path.exists() && !isWriteMode())
        throw Exception("File " + pathStr + " not found", Path::NotFound);

    if (path.exists() && path.isDirectory())
        throw Exception(pathStr + " is not file, it is directory", Path::NotFile);

    if (isOpen())
        close();

    m_file = fopen(pathStr.c_str(), getModeStr());
    m_mode = mode;
}

void File::close() {
    if (!isOpen())
        cerr << "Can't close file: file not opened";
    else {
        fclose(m_file);
        m_file = nullptr;
    }
}

size_t File::write(const void *data, const size_t size, const size_t elementSize) {
    return fwrite(data, elementSize, size, m_file);
}

size_t File::write(const Array<byte> &data) {
    return write(data.array(), data.size());
}

size_t File::write(const string &str) {
    return write(str.c_str(), str.length());
}

size_t File::read(void *buffer, size_t size, size_t count) const {
    return fread(buffer, size, count, m_file);
}

Array<byte> File::read() {
    size_t fileSize;

    seek(0, Origin::Start);

    if (m_mode == Mode::ReadText || m_mode == Mode::AppendText) {
        // If the given stream is opened in text mode, Windows-style newlines are converted into
        // Unix-style newlines. That is, carriage return-line feed (CRLF) pairs are replaced by
        // single line feed (LF) characters.
        // Thus, the file size may be larger than the received data
        // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fread

        fileSize = 0;

        auto isEOF = [&]() {
            fgetc(m_file);
            return feof(m_file);
        };

        while (!isEOF()) {
            ++fileSize;
        }

        seek(0, Origin::Start);
    } else {
        fileSize = size();
    }

    Array<byte> result(fileSize);
    read(result.m_array, 1, fileSize);

    return result;
}

string File::readStr() {
    auto data = read();
    return string(reinterpret_cast<char const *>(data.array()), data.size());
}

int File::seek(long offset, Origin origin) {
    return fseek(m_file, offset, static_cast<int>(origin));
}

bool File::isOpen() const {
    return m_file;
}

long File::tell() const {
    return ftell(m_file);
}

size_t File::size() const {
    auto prevPos = tell();

    fseek(m_file, 0, SEEK_END);
    size_t fileSize = tell();
    fseek(m_file, prevPos, SEEK_SET);

    return fileSize;
}

File::Mode File::getMode() const {
    return m_mode;
}
}
#include <tulz/DirectoryVisitor.h>

#include <tulz/Path.h>

using namespace std;

namespace tulz {
DirectoryVisitor::DirectoryVisitor(const string &dir) {
    set(dir);
    visit();
}

DirectoryVisitor::DirectoryVisitor() = default;

DirectoryVisitor::~DirectoryVisitor() {
    restore();
}

void DirectoryVisitor::set(const string &dir) {
    m_dir = dir;
}

const string& DirectoryVisitor::get() const {
    return m_dir;
}

void DirectoryVisitor::visit() {
    m_oldDir = Path::getWorkingDirectory();

    Path::setWorkingDirectory(m_dir);
}

void DirectoryVisitor::restore() {
    Path::setWorkingDirectory(m_oldDir);
}
}

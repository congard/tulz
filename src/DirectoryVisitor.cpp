#include <tulz/DirectoryVisitor.h>

namespace tulz {
DirectoryVisitor::DirectoryVisitor(const Path &dir) {
    set(dir);
    visit();
}

DirectoryVisitor::DirectoryVisitor() = default;

DirectoryVisitor::~DirectoryVisitor() {
    restore();
}

void DirectoryVisitor::set(const Path &dir) {
    m_dir = dir;
}

const Path& DirectoryVisitor::get() const {
    return m_dir;
}

void DirectoryVisitor::visit() {
    if (!m_dir.toString().empty()) {
        m_oldDir = Path::getWorkingDirectory();
        Path::setWorkingDirectory(m_dir);
    }
}

void DirectoryVisitor::restore() {
    if (!m_oldDir.toString().empty()) {
        Path::setWorkingDirectory(m_oldDir);
    }
}
}

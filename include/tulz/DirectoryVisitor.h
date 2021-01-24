#ifndef TULZ_DIRECTORYVISITOR_H
#define TULZ_DIRECTORYVISITOR_H

#include <tulz/Path.h>

namespace tulz {
class DirectoryVisitor {
public:
    explicit DirectoryVisitor(const Path &dir);
    DirectoryVisitor();
    ~DirectoryVisitor();

    void set(const Path &dir);
    const Path& get() const;

    void visit();
    void restore();

private:
    Path m_dir, m_oldDir;
};
}

#endif //TULZ_DIRECTORYVISITOR_H

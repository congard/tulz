#ifndef TULZ_DIRECTORYVISITOR_H
#define TULZ_DIRECTORYVISITOR_H

#include <string>

namespace tulz {
class DirectoryVisitor {
public:
    explicit DirectoryVisitor(const std::string &dir);
    DirectoryVisitor();
    ~DirectoryVisitor();

    void set(const std::string &dir);
    const std::string& get() const;

    void visit();
    void restore();

private:
    std::string m_dir, m_oldDir;
};
}

#endif //TULZ_DIRECTORYVISITOR_H

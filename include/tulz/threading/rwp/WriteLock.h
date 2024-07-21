#ifndef TULZ_WRITELOCK_H
#define TULZ_WRITELOCK_H

#include <tulz/threading/rwp/Resource.h>

namespace tulz::rwp {
class WriteLock {
public:
    explicit inline WriteLock(Resource &resource)
        : m_resource(resource)
    {
        m_resource.lockWrite();
    }

    inline ~WriteLock() {
        m_resource.unlockWrite();
    }

private:
    Resource &m_resource;
};
} // tulz::rwp

#endif //TULZ_WRITELOCK_H

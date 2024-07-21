#ifndef TULZ_READLOCK_H
#define TULZ_READLOCK_H

#include <tulz/threading/rwp/Resource.h>

namespace tulz::rwp {
class ReadLock {
public:
    explicit inline ReadLock(Resource &resource)
        : m_resource(resource)
    {
        m_resource.lockRead();
    }

    inline ~ReadLock() {
        m_resource.unlockRead();
    }

private:
    Resource &m_resource;
};
} // tulz::rwp

#endif //TULZ_READLOCK_H

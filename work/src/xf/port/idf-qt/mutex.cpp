#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_MUTEX_IMPLEMENTATION != 0)

#include "mutex.h"

XFMutexPort::XFMutexPort()
{
    _mutex();
}

XFMutexPort::~XFMutexPort()
{

}

void XFMutexPort::lock()
{
    _mutex.lock();
}

void XFMutexPort::unlock()
{
    _mutex.unlock();
}

bool XFMutexPort::tryLock(int32_t timeout)
{
    _mutex.tryLock(timeout);
}
#endif // USE_XF_PORT_IDF_QT_MUTEX_IMPLEMENTATION

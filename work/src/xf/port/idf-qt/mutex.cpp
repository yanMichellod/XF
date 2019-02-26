#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_MUTEX_IMPLEMENTATION != 0)

#include "mutex.h"

/**
 * @brief Constructor of XFMutexPort that create a QMutex.
 */
XFMutexPort::XFMutexPort():_mutex()
{
}
/**
 * @brief Destructor of XFMutexPort. Do nothing
 */
XFMutexPort::~XFMutexPort()
{

}
/**
 * @brief Lock the mutex.
 */
void XFMutexPort::lock()
{
    _mutex.lock();
}
/**
 * @brief Unlock the mutex.
 */
void XFMutexPort::unlock()
{
    _mutex.unlock();
}
/**
 * @brief Attempt to lock the mutex.
 * @param timeout integer argument. The function will wait at most this timeout for the mutex is available
 * Using a negative value is the same that call lock()
 * @return return True if the lock is obtaines otherwise False
 */
bool XFMutexPort::tryLock(int32_t timeout)
{
    return _mutex.tryLock(timeout);
}
#endif // USE_XF_PORT_IDF_QT_MUTEX_IMPLEMENTATION

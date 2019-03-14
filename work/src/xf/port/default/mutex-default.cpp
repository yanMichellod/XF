#include <config/xf-config.h>

#if (USE_XF_MUTEX_DEFAULT_IMPLEMENTATION != 0)

#include "critical/critical.h"	// Provided by the platform used
#include "mutex-default.h"

/**
 * @brief XFMutexDefault::XFMutexDefault
 */
XFMutexDefault::XFMutexDefault(){

}

/**
 * @brief XFMutexDefault::~XFMutexDefault
 */
XFMutexDefault::~XFMutexDefault(){

}

/**
 * @brief XFMutexDefault::lock lock the mutex
 */
void XFMutexDefault::lock(){
    /// disable interruption
    enterCritical();
}

/**
 * @brief XFMutexDefault::unlock unlock the mutex
 */
void XFMutexDefault::unlock(){
    /// enable interruption
    exitCritical();
}

/**
 * @brief XFMutexDefault::tryLock Not implemented on STM32
 * @param timeout
 * @return
 */
bool XFMutexDefault::tryLock(int32_t timeout){
	return true;
}
#endif // USE_XF_MUTEX_DEFAULT_IMPLEMENTATION

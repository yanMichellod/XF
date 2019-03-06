#include <config/xf-config.h>

#if (USE_XF_MUTEX_DEFAULT_IMPLEMENTATION != 0)

#include "critical/critical.h"	// Provided by the platform used
#include "mutex-default.h"

/**
 *Constructor of XFMutexDefault
 */
XFMutexDefault::XFMutexDefault(){

}

/**
 * Destructor of XFMutexDefault
 */
XFMutexDefault::~XFMutexDefault(){

}

/**
 * lock the mutex
 */
void XFMutexDefault::lock(){
	enterCritical();
}

/**
 * unlock the mutex
 */
void XFMutexDefault::unlock(){
	exitCritical();
}

bool XFMutexDefault::tryLock(int32_t timeout){

	return true;
}
#endif // USE_XF_MUTEX_DEFAULT_IMPLEMENTATION

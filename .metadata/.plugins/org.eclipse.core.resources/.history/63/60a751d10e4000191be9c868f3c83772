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
virtual XFMutexDefault::~XFMutexDefault(){

}

/**
 * lock the mutex
 */
virtual void XFMutexDefault::lock(){
	enterCritical();
}

/**
 * unlock the mutex
 */
virtual void XFMutexDefault::unlock(){
	exitCritical();
}

virtual bool XFMutexDefault::tryLock(int32_t timeout = 0){

	return true;
}
#endif // USE_XF_MUTEX_DEFAULT_IMPLEMENTATION

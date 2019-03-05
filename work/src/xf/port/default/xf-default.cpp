#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DEFAULT_IMPLEMENTATION != 0)

#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"

using interface::XFResourceFactory;
using interface::XFTimeoutManager;

void XF_initialize(int timeInterval){
	XF::initialize(timeInterval);
}
void XF_exec(){
	XF::exec();
}
void XF_execOnce(){
	XF::execOnce();
}
#endif // USE_XF_DEFAULT_IMPLEMENTATION

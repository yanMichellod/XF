#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DEFAULT_IMPLEMENTATION != 0)

#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"
#include "mdw/trace/trace.h"

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

void XF::initialize(int timeInterval, int argc, char* argv[]) {
	interface::XFResourceFactory::getInstance()->getDefaultDispatcher()->start();
	interface::XFTimeoutManager::getInstance()->initialize(timeInterval);
	interface::XFTimeoutManager::getInstance()->start();
}

int XF::exec() {
	while(true){

	}
}

int XF::execOnce() {
	interface::XFResourceFactory::getInstance()->getDefaultDispatcher()->executeOnce();
	return 1;
}

interface::XFDispatcher* XF::getDefaultDispatcher() {
	return interface::XFResourceFactory::getInstance()->getDefaultDispatcher();
}

int XF::kill() {
	return 1;
}

#endif // USE_XF_DEFAULT_IMPLEMENTATION

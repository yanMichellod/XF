
#include <config/xf-config.h>

#if (USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "xf/interface/reactive.h"
#include "xf/interface/resourcefactory.h"
#include "port-functions.h"
#include "timeoutmanager-default.h"

using interface::XFResourceFactory;

XFTimeoutManagerDefault::XFTimeoutManagerDefault():_timeouts()
{
    _pMutex = interface::XFResourceFactory::getInstance()->createMutex();
}


XFTimeoutManagerDefault::~XFTimeoutManagerDefault()
{
    delete _pMutex;
}

interface::XFTimeoutManager * interface::XFTimeoutManager::getInstance()
{
	return XFTimeoutManagerDefault::getInstance();
}

interface::XFTimeoutManager *XFTimeoutManagerDefault::getInstance()
{
    static interface::XFTimeoutManager* instance = nullptr;
    if (instance == nullptr){
        instance = new interface::XFTimeoutManager();
    }
    return instance;
}

void XFTimeoutManagerDefault::start()
{
    startTimer(getTickInterval());
}

void XFTimeoutManagerDefault::scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive *pReactive)
{

}

void XFTimeoutManagerDefault::unscheduleTimeout(int32_t timeoutId, interface::XFReactive *pReactive)
{

}

void XFTimeoutManagerDefault::tick()
{

}

void XFTimeoutManagerDefault::addTimeout(XFTimeout *pNewTimeout)
{

}

void XFTimeoutManagerDefault::removeTimeouts(int32_t timeoutId, interface::XFReactive *pReactive)
{

}

void XFTimeoutManagerDefault::returnTimeout(XFTimeout *pTimeout)
{

}

void XFTimeoutManagerDefault::timerEvent(QTimerEvent *event)
{
    tick();
}

// TODO: Implement code for XFTimeoutManagerDefault class

#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION



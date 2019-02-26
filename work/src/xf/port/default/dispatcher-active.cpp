#include <config/xf-config.h>

#if (USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#if (XF_TRACE_EVENT_PUSH_POP != 0)
    #include "trace/trace.h"
#endif // XF_TRACE_EVENT_PUSH_POP
#include "xf/eventstatus.h"
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/reactive.h"
#include "xf/interface/thread.h"
#include "xf/interface/resourcefactory.h"
#include "dispatcher-active.h"

using interface::XFTimeoutManager;
using interface::XFResourceFactory;

// TODO: Implement code for XFDispatcherActive class



XFDispatcherActiveDefault::XFDispatcherActiveDefault():_events()
{
    _bInitialized = false;
    _bExecuting = false;
    _pMutex = interface::XFResourceFactory::getInstance()->createMutex();
    _pThread = interface::XFResourceFactory::getInstance()->createThread();
}

XFDispatcherActiveDefault::~XFDispatcherActiveDefault()
{
    delete _pMutex;
    delete _pThread;
}

void XFDispatcherActiveDefault::initialize()
{
    _bInitialized = true;
}

void XFDispatcherActiveDefault::start()
{
    _pThread->start();
    _bExecuting = true;
}

void XFDispatcherActiveDefault::stop()
{
    _pThread->stop();
    _bExecuting = false;
}

void XFDispatcherActiveDefault::pushEvent(XFEvent *pEvent)
{
    _events.push(pEvent);
}

void XFDispatcherActiveDefault::scheduleTimeout(int timeoutId, int interval, interface::XFReactive *pReactive)
{

}

void XFDispatcherActiveDefault::unscheduleTimeout(int timeoutId, interface::XFReactive *pReactive)
{

}

int XFDispatcherActiveDefault::executeOnce()
{
    /// can not be called if start() has been executed
    if(_bExecuting == true){
        return -1;
    }
}

int XFDispatcherActiveDefault::execute(const void *param)
{

}

void XFDispatcherActiveDefault::dispatchEvent(const XFEvent *pEvent) const
{

}

#endif // USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION

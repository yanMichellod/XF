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
    _pThread = interface::XFResourceFactory::getInstance()->createThread(this,
                                                                         &execute,
                                                                         "Thread behavior",
                                                                         0);
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

/**
 * @brief push an event inside the queue waiting to be dispatched
 * @param pEvent Event to be dispatched
 */
void XFDispatcherActiveDefault::pushEvent(XFEvent *pEvent)
{
    _events.push(pEvent);
}

/**
 * @brief schedule a timeout with an instance of the timeout manager
 * @param timeoutId
 * @param interval
 * @param pReactive
 */
void XFDispatcherActiveDefault::scheduleTimeout(int timeoutId, int interval, interface::XFReactive *pReactive)
{
    XFTimeoutManager::getInstance()->scheduleTimeout(timeoutId,interval,pReactive);
}

/**
 * @brief unschedule timer with an instance of the timeout manager
 * @param timeoutId
 * @param pReactive
 */
void XFDispatcherActiveDefault::unscheduleTimeout(int timeoutId, interface::XFReactive *pReactive)
{
    XFTimeoutManager::getInstance()->unscheduleTimeout(timeoutId,pReactive);
}

int XFDispatcherActiveDefault::executeOnce()
{
    /// can not be called if start() has not been executed
    if(_bExecuting == true){
        return -1;
    }
    else{
        if(!_events.empty()){
            //execute(_events.pop());
        }
    }
}

int XFDispatcherActiveDefault::execute(const void *param)
{

}

void XFDispatcherActiveDefault::dispatchEvent(const XFEvent *pEvent) const
{

}

#endif // USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION

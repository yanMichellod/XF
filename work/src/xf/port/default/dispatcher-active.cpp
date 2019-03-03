#include <config/xf-config.h>

#if (USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#if (XF_TRACE_EVENT_PUSH_POP != 0)
    #include "trace/trace.h"
#endif // XF_TRACE_EVENT_PUSH_POP
#include "xf/eventstatus.h"
#include "trace/trace.h"
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/reactive.h"
#include "xf/interface/thread.h"
#include "xf/interface/resourcefactory.h"
#include "xf/xf.h"
#include "dispatcher-active.h"

using interface::XFTimeoutManager;
using interface::XFResourceFactory;

XFDispatcherActiveDefault::XFDispatcherActiveDefault() :
    _bInitialized(false),
    _bExecuting(false),
    _pThread(nullptr),
    _pMutex(nullptr)
{
    // Create Thread
    _pThread = XFResourceFactory::getInstance()->createThread(this,
                                                              (interface::XFThread::EntryMethodBody)&XFDispatcherActiveDefault::execute,
                                                              "dispatcherThread");
    assert(_pThread);
    if (!_bInitialized)
    {
        _bInitialized = true;
        _pMutex = XFResourceFactory::getInstance()->createMutex();
        assert(_pMutex);
    }
}

XFDispatcherActiveDefault::~XFDispatcherActiveDefault()
{
    _bExecuting = false;
}

void XFDispatcherActiveDefault::initialize()
{
}

void XFDispatcherActiveDefault::start()
{
    assert(_pThread);
    assert(_pMutex);        // Call initialize() first
    _bExecuting = true;
    _pThread->start();


}

void XFDispatcherActiveDefault::stop()
{
    _bExecuting = false;
    _pThread->stop();
    XF::kill();
}

void XFDispatcherActiveDefault::pushEvent(XFEvent * pEvent)
{
    if (!_bInitialized)
    {
        initialize();
    }

    _pMutex->lock();
    {
//#if (XF_TRACE_EVENT_PUSH_POP != 0)
        //Trace::out("Push event: 0x%x  \n---------------------", pEvent);
//#endif // XF_TRACE_EVENT_PUSH_POP
        _events.push(pEvent);
    }
    _pMutex->unlock();
}

void XFDispatcherActiveDefault::scheduleTimeout(int timeoutId, int interval, interface::XFReactive * pReactive)
{
    // Forward timeout to the timeout manager
    XFTimeoutManager::getInstance()->scheduleTimeout(timeoutId, interval, pReactive);
}

void XFDispatcherActiveDefault::unscheduleTimeout(int timeoutId, interface::XFReactive * pReactive)
{
    // Forward timeout to the timeout manager
    XFTimeoutManager::getInstance()->unscheduleTimeout(timeoutId, pReactive);
}

int XFDispatcherActiveDefault::execute(const void * param /* = nullptr */)
{
    (void)param;
    while(_bExecuting)
    {
        while (_events.empty() && _bExecuting)
        {
            _events.pend();	// Wait until something to do
        }

        executeOnce();
    }

    return 0;
}

int XFDispatcherActiveDefault::executeOnce()
{
    // TODO: Implement code
    dispatchEvent(_events.front());
    return _bExecuting;
}

void XFDispatcherActiveDefault::dispatchEvent(const XFEvent * pEvent) const
{
    // TODO: Implement code
    XFEventStatus status = pEvent->getBehavior()->process(pEvent);
    if(status == XFEventStatus::Consumed){
        /// delete the consumed Event
        delete pEvent;
    }
    else if(status == XFEventStatus::Terminate){
        interface::XFResourceFactory::getInstance()->getDefaultDispatcher()->stop();
    }
}


#endif // USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION

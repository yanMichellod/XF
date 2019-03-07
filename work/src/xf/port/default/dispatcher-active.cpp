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

/**
 * @brief XFDispatcherActiveDefault::XFDispatcherActiveDefault
 * Constructor of the default dispatcher which contains a thread and a mutex
 */
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

/**
 * @brief XFDispatcherActiveDefault::~XFDispatcherActiveDefault
 * Destructor of the default dispatcher
 */
XFDispatcherActiveDefault::~XFDispatcherActiveDefault()
{
    _bExecuting = false;
    delete interface::XFResourceFactory::getInstance()->getDefaultDispatcher();
    delete interface::XFResourceFactory::getInstance();
}

/**
 * @brief XFDispatcherActiveDefault::initialize
 * All object needed for this class is create in the Constructor
 */
void XFDispatcherActiveDefault::initialize()
{
}

/**
 * @brief XFDispatcherActiveDefault::start start the thread to execute XFDispatcherActiveDefault::execute()
 */
void XFDispatcherActiveDefault::start()
{
    assert(_pThread);
    assert(_pMutex);
    _bExecuting = true;
    _pThread->start();


}

/**
 * @brief XFDispatcherActiveDefault::stop
 * stop the thread and the main thread
 */
void XFDispatcherActiveDefault::stop()
{
    _bExecuting = false;
    _pThread->stop();
    //XF::kill();
}

/**
 * @brief XFDispatcherActiveDefault::pushEvent
 * @param pEvent event to push in the list of event to dispatch
 */
void XFDispatcherActiveDefault::pushEvent(XFEvent * pEvent)
{
    if (!_bInitialized)
    {
        initialize();
    }

    _pMutex->lock();
    {
        _events.push(pEvent);
    }
    _pMutex->unlock();
}

/**
 * @brief XFDispatcherActiveDefault::scheduleTimeout Schedule timeout
 * @param timeoutId Id of the timeout
 * @param interval interval in milliseconds the timeout must wait
 * @param pReactive the reactive class where the timeout must be launch
 */
void XFDispatcherActiveDefault::scheduleTimeout(int timeoutId, int interval, interface::XFReactive * pReactive)
{
    // Forward timeout to the timeout manager
    XFTimeoutManager::getInstance()->scheduleTimeout(timeoutId, interval, pReactive);
}

/**
 * @brief XFDispatcherActiveDefault::unscheduleTimeout unschedule timeout
 * @param timeoutId Id of the timeout to cancel
 * @param pReactive the reactive class where the timeout must be launch
 */
void XFDispatcherActiveDefault::unscheduleTimeout(int timeoutId, interface::XFReactive * pReactive)
{
    // Forward timeout to the timeout manager
    XFTimeoutManager::getInstance()->unscheduleTimeout(timeoutId, pReactive);
}

/**
 * @brief XFDispatcherActiveDefault::execute method executed by the tread
 * this blocking method wait until an event is pushed in the list of event
 * @param param
 * @return
 */
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

/**
 * @brief XFDispatcherActiveDefault::executeOnce called by execute() to dispatch only one event
 * @return
 */
int XFDispatcherActiveDefault::executeOnce()
{
    // TODO: Implement code
    dispatchEvent(_events.front());
    return _bExecuting;
}
/**
 * @brief XFDispatcherActiveDefault::dispatchEvent Dispatch the event to the right activ class.
 * The event is deleted if it was consumed.
 * The dispatcher is stopped if the class which process the event send back a XFEventStatus::Terminate
 * @param pEvent Event to dispatch
 */
void XFDispatcherActiveDefault::dispatchEvent(const XFEvent * pEvent) const
{
    // TODO: Implement code
    XFEventStatus status = pEvent->getBehavior()->process(pEvent);
    if(status == XFEventStatus::Consumed){
        /// delete the consumed Event
        delete pEvent;
        pEvent = nullptr;
    }
    else if(status == XFEventStatus::Terminate){
        delete pEvent->getBehavior();
        delete pEvent;
        pEvent = nullptr;
    }
}


#endif // USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION

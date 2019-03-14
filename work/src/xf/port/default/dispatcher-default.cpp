#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION != 0)
#if (XF_TRACE_EVENT_PUSH_POP != 0)
    #include "trace/trace.h"
#endif // XF_TRACE_EVENT_PUSH_POP
#include "xf/eventstatus.h"
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/reactive.h"
#include "xf/interface/resourcefactory.h"
#include "mdw/trace/trace.h"
#include "dispatcher-default.h"

using interface::XFTimeoutManager;
using interface::XFResourceFactory;

/**
 * @brief XFDispatcherDefault::XFDispatcherDefault
 */
XFDispatcherDefault::XFDispatcherDefault():_events(){
	_bExecuting = false;
	_bInitialized = false;
	_pMutex = interface::XFResourceFactory::getInstance()->createMutex();
}
/**
 * @brief XFDispatcherDefault::~XFDispatcherDefault
 */
XFDispatcherDefault::~XFDispatcherDefault(){
	delete _pMutex;
}

/**
 * @brief XFDispatcherDefault::initialize initialize the dispatcher
 */
void XFDispatcherDefault::initialize(){
	_bInitialized = true;
}

/**
 * @brief XFDispatcherDefault::start start the dispatcher
 */
void XFDispatcherDefault::start(){
	_bExecuting = true;
}

/**
 * @brief XFDispatcherDefault::stop stop the dispatcher
 */
void XFDispatcherDefault::stop(){
	_bExecuting = false;
}

/**
 * @brief XFDispatcherDefault::pushEvent push an event in the queue
 * @param pEvent Event to store in the queue
 */
void XFDispatcherDefault::pushEvent(XFEvent * pEvent){
	if(!_bInitialized){
		initialize();
	}
	_pMutex->lock();
	_events.push(pEvent);
	_pMutex->unlock();
}

/**
 * @brief XFDispatcherDefault::scheduleTimeout
 * @param timeoutId Id of the timeout
 * @param interval Interval the timeout must wait
 * @param pReactive Pointer of the class where the timeout must be sent
 */
void XFDispatcherDefault::scheduleTimeout(int timeoutId, int interval, interface::XFReactive * pReactive){
	interface::XFTimeoutManager::getInstance()->scheduleTimeout(timeoutId, interval, pReactive);
}

/**
 * @brief XFDispatcherDefault::unscheduleTimeout
 * @param timeoutId Id of the timeout to remove
 * @param pReactive Pointer of the reactive class of the timeout to remove
 */
void XFDispatcherDefault::unscheduleTimeout(int timeoutId, interface::XFReactive * pReactive){
	interface::XFTimeoutManager::getInstance()->unscheduleTimeout(timeoutId, pReactive);
}

/**
 * @brief XFDispatcherDefault::executeOnce method to call continuously
 * @return
 */
int XFDispatcherDefault::executeOnce(){
	_events.pend();
	dispatchEvent(_events.front());
	_events.pop();
	return 1;
}

/**
 * @brief XFDispatcherDefault::execute Do nothing on STM32 plateform
 * @param param
 * @return
 */
int XFDispatcherDefault::execute(const void * param){
	return 0;
}

/**
 * @brief XFDispatcherDefault::dispatchEvent dispatch an event to the appropriate class
 * @param pEvent Event to dispactch
 */
void XFDispatcherDefault::dispatchEvent(const XFEvent * pEvent) const{
    /// send event
    XFEventStatus status = pEvent->getBehavior()->process(pEvent);
    /// delete event
    if(status == XFEventStatus::Consumed){
        delete pEvent;
        pEvent = nullptr;
    }
    else if(status == XFEventStatus::Terminate){
        delete pEvent;
        pEvent = nullptr;
    }
}


#endif // USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION

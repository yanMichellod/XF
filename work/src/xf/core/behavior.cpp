#include <assert.h>
#include "xf/xf.h"
#include "trace/trace.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/timeout.h"
#include "xf/initialevent.h"
#include "xf/behavior.h"

using interface::XFResourceFactory;

/**
 * @brief XFBehavior::XFBehavior Constructor of the XFBehavior class
 * @param pDispatcher pointer to the dispatcher
 */
XFBehavior::XFBehavior(interface::XFDispatcher *pDispatcher)
{
    _pDispatcher = pDispatcher;
    _isActive = false;
    _pCurrentEvent = nullptr;
}

/**
 * @brief XFBehavior::XFBehavior Constructor of the XFBehavior class if a default dispatcher is needed
 * @param ownDispatcher
 */
XFBehavior::XFBehavior(bool ownDispatcher)
{
    if(ownDispatcher){
        _pDispatcher = nullptr;
        _isActive = false;
        _pCurrentEvent = nullptr;
    }
}

/**
 * @brief XFBehavior::~XFBehavior Destructor of the XFBehavior class
 */
XFBehavior::~XFBehavior()
{

}

/**
 * @brief XFBehavior::startBehavior Start behavior of the dispatcher with an initial event
 */
void XFBehavior::startBehavior()
{
    pushEvent(new XFEvent(XFEvent::Initial, 1,this));
}

/**
 * @brief XFBehavior::pushEvent push event to the queue of the dispatcher
 * @param pEvent Event to dispatch
 */
void XFBehavior::pushEvent(XFEvent *pEvent)
{
    if(_pDispatcher == nullptr){
        interface::XFResourceFactory::getInstance()->getDefaultDispatcher()->pushEvent(pEvent);
    }
    else{
        getDispatcher()->pushEvent(pEvent);
    }
}

/**
 * @brief XFBehavior::getCurrentEvent
 * @return a pointer to the current event
 */
const XFEvent* XFBehavior::getCurrentEvent() const
{
    return _pCurrentEvent;
}

/**
 * @brief XFBehavior::getDispatcher
 * @return Pointer to the dispatcher
 */
interface::XFDispatcher* XFBehavior::getDispatcher()
{
    interface::XFDispatcher* retVal = nullptr;
    if(_pDispatcher == nullptr){
        retVal = interface::XFResourceFactory::getInstance()->getDefaultDispatcher();
    }
    else{
        retVal = _pDispatcher;
    }
    return retVal;
}

/**
 * @brief XFBehavior::getCurrentTimeout get the timeout only if the current event is a timeout
 * @return pointer to the current timeout
 */
const XFTimeout* XFBehavior::getCurrentTimeout()
{
    if(_pCurrentEvent->getEventType() == XFEvent::Timeout){
        return (XFTimeout*)_pCurrentEvent;
    }
    return nullptr;
}

/**
 * @brief XFBehavior::setCurrentEvent
 * @param pEvent Event to
 */
void XFBehavior::setCurrentEvent(const XFEvent *pEvent)
{
    _pCurrentEvent = pEvent;
}

/**
 * @brief XFBehavior::process see the behavior.h
 * @param pEvent event to process
 * @return the status of process
 * It could be Unknown, Consumed, NotConsumed, RegionFinished, Terminate.
 */
XFEventStatus XFBehavior::process(const XFEvent *pEvent)
{
    setCurrentEvent(pEvent);
    XFEventStatus retVal = processEvent();
    return retVal;
}

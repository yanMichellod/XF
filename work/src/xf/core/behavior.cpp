#include <assert.h>
#include "xf/xf.h"
#include "trace/trace.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/timeout.h"
#include "xf/initialevent.h"
#include "xf/behavior.h"
#include <typeinfo>

using interface::XFResourceFactory;

XFBehavior::XFBehavior(interface::XFDispatcher *pDispatcher)
{
    _pDispatcher = pDispatcher;
    _isActive = false;
    _pCurrentEvent = nullptr;
}

XFBehavior::XFBehavior(bool ownDispatcher)
{
    if(ownDispatcher){
        _pDispatcher = nullptr;
        _isActive = false;
        _pCurrentEvent = nullptr;
    }
}

XFBehavior::~XFBehavior()
{

}

void XFBehavior::startBehavior()
{
    Trace::out("Push initial Event ...\n---------------------");
    pushEvent(new XFInitialEvent());
}

void XFBehavior::pushEvent(XFEvent *pEvent)
{
    if(_pDispatcher == nullptr){
        Trace::out("call Default dispatcher ...\n---------------------");
        interface::XFResourceFactory::getInstance()->getDefaultDispatcher()->pushEvent(pEvent);
    }
    else{
        getDispatcher()->pushEvent(pEvent);
    }
}

const XFEvent* XFBehavior::getCurrentEvent() const
{
    return _pCurrentEvent;
}

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

const XFTimeout* XFBehavior::getCurrentTimeout()
{
    if(_pCurrentEvent->getEventType() == XFEvent::Timeout){
        return (XFTimeout*)_pCurrentEvent;
    }
    return nullptr;
}

void XFBehavior::setCurrentEvent(const XFEvent *pEvent)
{
    _pCurrentEvent = pEvent;
}

XFEventStatus XFBehavior::process(const XFEvent *pEvent)
{
    _pCurrentEvent = pEvent;
    processEvent();
}

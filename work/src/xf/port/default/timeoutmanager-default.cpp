
#include <config/xf-config.h>

#if (USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include <trace/trace.h>
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
        instance = new XFTimeoutManagerDefault();
    }
    return instance;
}

void XFTimeoutManagerDefault::start()
{
    Trace::out("Start XFTimeoutManager...\n---------------------");
    XF_startTimeoutManagerTimer(getTickInterval());
}

void XFTimeoutManagerDefault::scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive *pReactive)
{
    /// create tempTimout to insert in the list
    XFTimeout* tempTimeout = new XFTimeout(timeoutId, interval, pReactive);
    /// call addTimeout method
    addTimeout(tempTimeout);
}

void XFTimeoutManagerDefault::unscheduleTimeout(int32_t timeoutId, interface::XFReactive *pReactive)
{
    /// call removeTimeouts method
    removeTimeouts(timeoutId, pReactive);
}

void XFTimeoutManagerDefault::tick()
{
    ///substract relative tick of the first element of the list if the list is not empty
    if(!_timeouts.empty()){
        _timeouts.front()->substractFromRelTicks(1);
        /// the event is timeout
        if(_timeouts.front()->getRelTicks() == 0){
            /**
            * WORK IN PROGRESS
            * DON'T SURE IT WORKS
            */
            if(_timeouts.front()->deleteAfterConsume() == false){
                returnTimeout(_timeouts.front());
                addTimeout(_timeouts.front());
            }
            _timeouts.pop_front();
         }
    }
}

void XFTimeoutManagerDefault::addTimeout(XFTimeout *pNewTimeout)
{
    /// WARNING !!!!! Maybe the mutex must protect all this method
    /// if the timeout is the first in the list
    if(_timeouts.empty() == true){
        pNewTimeout->setRelTicks(pNewTimeout->getInterval());
        _timeouts.push_front(pNewTimeout);
    }
    /// another timeout already exist
    else{
        int relTickTot = 0;
        bool inserted = false;
        /// browse the list the find the correct position according to the relative tick
        _pMutex->lock();
        for(XFTimeout* timeout : _timeouts){
            relTickTot = relTickTot + timeout->getRelTicks();
            /// find the correct place to insert the new timeout
            if(relTickTot > pNewTimeout->getInterval()){
                /// set relative tick of new timeout
                pNewTimeout->setRelTicks(relTickTot-timeout->getRelTicks());
                /// insert new timeout before the actual pointer of timeout
                auto it = std::find(_timeouts.begin(), _timeouts.end(), timeout);
                if (it != _timeouts.end()) {
                    _timeouts.insert(it, pNewTimeout);
                    inserted = true;
                }
            }
            if(inserted){
                timeout->setRelTicks(timeout->getRelTicks()-pNewTimeout->getRelTicks());
            }
        }
        _pMutex->unlock();
        /// the timeout was not inserted. it should be the last
        if(!inserted){
            pNewTimeout->setRelTicks(pNewTimeout->getInterval()-relTickTot);
            _timeouts.push_back(pNewTimeout);
        }
    }
}

void XFTimeoutManagerDefault::removeTimeouts(int32_t timeoutId, interface::XFReactive *pReactive)
{
    XFTimeout timeoutToRemove(timeoutId,0,pReactive);
    int removedRelTick = 0;
    bool removed = false;
    /// erase timeout according to it Id and it XFReactive
    _pMutex->lock();
    /// WARNING DON'T SURE IT WORK
    /// IN NO WORKING CASE USE ERASE METHOD FROM STD::LIST WITH ITERATOR
    for(XFTimeout*  temp: _timeouts){
        /// find the timeout to remove
        if(*temp == timeoutToRemove){
            removedRelTick = temp->getRelTicks();
            _timeouts.remove(temp);
            removed = true;
        }
       /// add relTick of the element removed in the list at the other element next to him
        if(removed){
            temp->addToRelTicks(removedRelTick);
        }
    }
    _pMutex->unlock();
}

void XFTimeoutManagerDefault::returnTimeout(XFTimeout *pTimeout)
{
    pTimeout->getBehavior()->pushEvent(pTimeout);
}


// TODO: Implement code for XFTimeoutManagerDefault class

#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION



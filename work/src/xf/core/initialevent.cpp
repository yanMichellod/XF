#include "xf/initialevent.h"

/**
 * @brief XFInitialEvent::XFInitialEvent Constructor of the XFInitialEvent
 * call the constructor of it parent XFEvent
 */
XFInitialEvent::XFInitialEvent():XFEvent(XFEvent::Initial, 0,nullptr)
{

}

/**
 * @brief XFInitialEvent::~XFInitialEvent Destructor of the XFInitialEvent
 */
XFInitialEvent::~XFInitialEvent()
{

}

/**
 * @brief XFInitialEvent::deleteAfterConsume
 * @return true if the event must be delete after has been consumed
 * false otherwise
 */
bool XFInitialEvent::deleteAfterConsume() const
{
    return true;
}

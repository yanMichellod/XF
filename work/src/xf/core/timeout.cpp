#include "xf/timeout.h"

/**
 * @brief XFTimeout::XFTimeout Constructor of the XFTimeout
 * call the constructor of it parent XFEvent
 * @param id Id of the timeout
 * @param interval Interval the timeout must wait before pop
 * @param pBehavior Pointer to the active class where the timeout must be send
 */
XFTimeout::XFTimeout(int id, int interval, interface::XFReactive *pBehavior):XFEvent(Timeout, id, pBehavior)
{
    _interval = interval;
    _relTicks = 0;
}

/**
 * @brief XFTimeout::~XFTimeout Destructor of the XFTimeout
 */
XFTimeout::~XFTimeout()
{

}
/**
 * @brief XFTimeout::operator == surcharged operator == to comparate two timeout
 * @param timeout
 * @return true if the two timeout have the same behavior and the same id
 *         otherwise false
 */
bool XFTimeout::operator ==(const XFTimeout &timeout) const
{
    if((_pBehavior == timeout.getBehavior()) && (_id == timeout.getId())){
        return true;
    }
    return false;
}

/**
 * @brief XFTimeout::deleteAfterConsume
 * @return true if the event must be delete after has been consumed
 * false otherwise
 */
bool XFTimeout::deleteAfterConsume() const
{
    return true;
}

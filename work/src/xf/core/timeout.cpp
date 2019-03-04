#include "xf/timeout.h"

XFTimeout::XFTimeout(int id, int interval, interface::XFReactive *pBehavior):XFEvent(Timeout, id, pBehavior)
{
    _interval = interval;
    _relTicks = 0;
}

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

bool XFTimeout::deleteAfterConsume() const
{
    return true;
}

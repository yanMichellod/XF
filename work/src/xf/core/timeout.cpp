#include "xf/timeout.h"

XFTimeout::XFTimeout(int id, int interval, interface::XFReactive *pBehavior):XFEvent(Timeout, id, pBehavior)
{
    _interval = interval;
    _relTicks = 0;
}

XFTimeout::~XFTimeout()
{

}

bool XFTimeout::operator ==(const XFTimeout &timeout) const
{
    if((_pBehavior == timeout.getBehavior()) && (_id == timeout.getId())){
        return true;
    }
    return false;
}

bool XFTimeout::deleteAfterConsume() const
{
    return false;
}

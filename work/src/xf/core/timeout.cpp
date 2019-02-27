#include "xf/timeout.h"

XFTimeout::XFTimeout(int id, int interval, interface::XFReactive *pBehavior):XFEvent(Timeout, _id, pBehavior)
{
    _interval = interval;
    _relTicks = 0;
}

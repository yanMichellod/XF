#include "evrestart.h"

evRestart::evRestart(interface::XFReactive *pBehavior) : XFCustomEvent(EventId::evRestart, pBehavior)
{
}

evRestart::~evRestart()
{
}

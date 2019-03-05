#include "xf/customevent.h"

/**
 * @brief XFCustomEvent::XFCustomEvent Constructor of XFCustomEvent
 * call the constructor of it parent XFEvent
 * @param id Id of the event
 * @param pBehavior pointer to the active to send back the event
 */
XFCustomEvent::XFCustomEvent(int id, interface::XFReactive *pBehavior):XFEvent(XFEvent::Event, id, pBehavior)
{

}

/**
 * @brief XFCustomEvent::~XFCustomEvent Destructor of the XFCustomEvent
 */
XFCustomEvent::~XFCustomEvent()
{

}

#include "xf/nulltransition.h"

/**
 * @brief XFNullTransition::XFNullTransition Constructor of XFNullTransition
 * call the constructor of it parent XFEvent

 */
XFNullTransition::XFNullTransition():XFEvent(XFEvent::NullTransition, 0 , nullptr)
{

}

/**
 * @brief XFNullTransition::~XFNullTransition Destructor of XFNullTransition
 */
XFNullTransition::~XFNullTransition()
{

}

/**
 * @brief XFNullTransition::deleteAfterConsume
 * @return true if the event must be delete after has been consumed
 * false otherwise
 */
bool XFNullTransition::deleteAfterConsume() const
{
    return true;
}

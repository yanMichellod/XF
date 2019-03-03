#include "xf/nulltransition.h"

XFNullTransition::XFNullTransition():XFEvent(XFEvent::NullTransition, 0 , nullptr)
{

}

XFNullTransition::~XFNullTransition()
{

}

bool XFNullTransition::deleteAfterConsume() const
{
    return true;
}

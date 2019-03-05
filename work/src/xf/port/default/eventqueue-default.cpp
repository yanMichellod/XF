#include <config/xf-config.h>

#if (USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "eventqueue-default.h"

// TODO: Implement code for XFEventQueueDefault class
XFEventQueueDefault::XFEventQueueDefault(){

}

virtual XFEventQueueDefault::~XFEventQueueDefault(){

}
virtual bool XFEventQueueDefault::empty() const{
	///< Returns true if no event is in the queue.
	return empty();
}
virtual bool XFEventQueueDefault::push(const XFEvent * pEvent){
   ///< Pushes the given event onto the queue.
	push(pEvent);
	return true;
}
virtual const XFEvent * XFEventQueueDefault::front(){
    ///< Returns pointer to next event to pop.
	return front();
}
virtual void XFEventQueueDefault::pop(){
 	///< Pops the next event from the queue.
	pop();
}
                                                        ///< Wait for the next event to arrive. Returns true if an event is in the queue.
virtual bool XFEventQueueDefault::pend(){

}
#endif // USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION

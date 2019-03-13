#include <config/xf-config.h>

#if (USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "eventqueue-default.h"

// TODO: Implement code for XFEventQueueDefault class
XFEventQueueDefault::XFEventQueueDefault(){

}

XFEventQueueDefault::~XFEventQueueDefault(){

}
bool XFEventQueueDefault::empty() const{
	///< Returns true if no event is in the queue.
	return _queue.empty();
}
bool XFEventQueueDefault::push(const XFEvent * pEvent){
   ///< Pushes the given event onto the queue.
	_queue.push(pEvent);
	return true;
}
const XFEvent * XFEventQueueDefault::front(){
    ///< Returns pointer to next event to pop.
	return _queue.front();
}
void XFEventQueueDefault::pop(){
 	///< Pops the next event from the queue.
	_queue.pop();
}
                                                        ///< Wait for the next event to arrive. Returns true if an event is in the queue.
bool XFEventQueueDefault::pend(){
	while(empty()){};
	return true;
}
#endif // USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION

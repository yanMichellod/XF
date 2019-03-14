#include <config/xf-config.h>

#if (USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "eventqueue-default.h"

/**
 * @brief XFEventQueueDefault::XFEventQueueDefault
 */
XFEventQueueDefault::XFEventQueueDefault(){

}

/**
 * @brief XFEventQueueDefault::~XFEventQueueDefault
 */
XFEventQueueDefault::~XFEventQueueDefault(){

}

/**
 * @brief XFEventQueueDefault::empty
 * @return true if the queue is empty therefore false
 */
bool XFEventQueueDefault::empty() const{
	///< Returns true if no event is in the queue.
	return _queue.empty();
}

/**
 * @brief XFEventQueueDefault::push push event onto the queue
 * @param pEvent Event to store
 * @return
 */
bool XFEventQueueDefault::push(const XFEvent * pEvent){
	_queue.push(pEvent);
	return true;
}

/**
 * @brief XFEventQueueDefault::front
 * @return the first element in the queue
 */
const XFEvent * XFEventQueueDefault::front(){
	return _queue.front();
}

/**
 * @brief XFEventQueueDefault::pop Pops the next event from the queue.
 */
void XFEventQueueDefault::pop(){
	_queue.pop();
}

/**
 * @brief XFEventQueueDefault::pend Wait for the next event to arrive
 * @return true if an event is in the queue.
 */
bool XFEventQueueDefault::pend(){
	while(empty()){};
	return true;
}
#endif // USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION

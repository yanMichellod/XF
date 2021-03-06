#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION != 0)

#include <assert.h>
#include "trace/trace.h"
#include <QtGlobal>
#include <QMutexLocker>
#include "eventqueue.h"
#include "xf/event.h"

// TODO: Implement code for XFEventQueuePort class


/**
 * @brief Constructor of XFEventQueue that create a QMutex, a QWaitCondition and EventQueue.
 * The EventQueue is a QQueue of EXEvent*.
 */
XFEventQueuePort::XFEventQueuePort():_mutex(),_newEvents(),_queue()
{

}

/**
 * @brief Destructor of XFEventQueue. Do nothing
 */
XFEventQueuePort::~XFEventQueuePort()
{
    for(auto e : _queue){
        if(e){
            delete e;
            e = nullptr;
        }
    }
}

/**
 * @return True if no event is in the queue.
 */
bool XFEventQueuePort::empty() const
{
    return _queue.isEmpty();
}

/**
 * @brief Method to push XFEvent in the tail of the queue
 * @param pointer of an XFEvent
 * @return True
 */
bool XFEventQueuePort::push(const XFEvent *pEvent)
{
    bool wasEmpty = empty();
    _mutex.lock();
    _queue.enqueue(pEvent);
    _mutex.unlock();
    if(wasEmpty == true){
        _newEvents.wakeAll();
    }
    return true;
}

/**
 * @brief Method to get a pointer of the next event to pop
 * @return A pointer to next event to pop
 */
const XFEvent *XFEventQueuePort::front()
{
    return _queue.dequeue();
}

/**
 * @brief Method to pop the event of the list
 */
void XFEventQueuePort::pop()
{
    _queue.pop_front();
}

/**
 * @brief Method to wait for the next event to arrive
 * @return True if an event is in the queue
 */
bool XFEventQueuePort::pend()
{
    bool isEmpty = empty();
    if(isEmpty == true){
        _mutex.lock();
        _newEvents.wait(&_mutex);
        _mutex.unlock();
    }
    return true;
}
#endif // USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION

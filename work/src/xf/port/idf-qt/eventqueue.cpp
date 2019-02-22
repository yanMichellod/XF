#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION != 0)

#include <assert.h>
#include <QtGlobal>
#include <QMutexLocker>
#include "eventqueue.h"

// TODO: Implement code for XFEventQueuePort class

#endif // USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION

XFEventQueuePort::XFEventQueuePort()
{
    _mutex();
    _newEvents();
    _queue();

}

XFEventQueuePort::~XFEventQueuePort()
{

}

bool XFEventQueuePort::empty() const
{
    return _queue.isEmpty();
}

bool XFEventQueuePort::push(const XFEvent *pEvent)
{
    _mutex.lock();
    _queue.enqueue(pEvent);
    _mutex.unlock();
}

const XFEvent *XFEventQueuePort::front()
{
    return _queue.head();
}

void XFEventQueuePort::pop()
{
    _queue.dequeue();
}

bool XFEventQueuePort::pend()
{

}

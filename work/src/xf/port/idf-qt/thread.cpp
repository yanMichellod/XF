#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION != 0)

#include <assert.h>
#include "trace/trace.h"
#include <string.h>
#include "thread.h"

#if !defined(XFTHREAD_DEFAULT_STACK_SIZE)
    #define XFTHREAD_DEFAULT_STACK_SIZE	256
#endif

/**
 * Always keep threads after creation in suspended state.
 * Threads must be explicitly started with start()!
 */

/**
 * @brief Constructor of the XFThreadPort
 * @param pProvider Provider of the method to execute
 * @param entryMethod Method to execute by the tread. It must be an infinite loop.
 * @param threadName Name of the tread
 * @param stackSize Size of the stack
 */
XFThreadPort::XFThreadPort(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
    _pEntryMethodProvider = pProvider;
    _entryMethod = entryMethod;
    setStackSize(stackSize);
    setObjectName(threadName);
}

/**
 * @brief override method from QThread. WARNING : Never call this method
 * it will be automatically called by QThread::start()
 * call the method of the provider
 */
void XFThreadPort::run()
{
    /// call the method passed during the construction of thread
     (_pEntryMethodProvider->*_entryMethod)(this);
}

/**
 * @brief Start method of the thread
 */
void XFThreadPort::start()
{
    QThread::start();
}

/**
 * @brief Block the thread
 */
void XFThreadPort::suspend()
{
    QThread::wait();
}

/**
 * @brief exit from the event loop
 */
void XFThreadPort::stop()
{
    QThread::exit();
}

/**
 * @brief Set priority of the thread
 * @param priority
 */
void XFThreadPort::setPriority(XFThreadPriority priority)
{
    switch (priority) {
    case XF_THREAD_PRIO_UNKNOWN :
    {
        QThread::setPriority(QThread::IdlePriority);
        break;
    }
    case XF_THREAD_PRIO_LOW:
    {
        QThread::setPriority(QThread::LowPriority);
        break;
    }
    case XF_THREAD_PRIO_NORMAL :
    {
        QThread::setPriority(QThread::NormalPriority);
        break;
    }
    case XF_THREAD_PRIO_HIGH :
    {
        QThread::setPriority(QThread::HighPriority);
        break;
    }
    case XF_THREAD_PRIO_MAX :
    {
        QThread::setPriority(QThread::HighestPriority);
        break;
    }
    default:
        break;
    }
}

/**
 * @brief get priority of the thread
 * @return
 */
XFThreadPriority XFThreadPort::getPriority() const
{
    switch(QThread::priority()){
    case QThread::IdlePriority:{
        return XF_THREAD_PRIO_UNKNOWN;
        break;
    }
    case QThread::LowPriority:{
        return XF_THREAD_PRIO_LOW;
        break;
    }
    case QThread::NormalPriority:{
        return XF_THREAD_PRIO_NORMAL;
        break;
    }
    case QThread::HighPriority:{
        return XF_THREAD_PRIO_HIGH;
        break;
    }
    case QThread::HighestPriority:{
        return XF_THREAD_PRIO_MAX;
        break;
    }
    default:
        break;
    }

    return XF_THREAD_PRIO_UNKNOWN;
}

/**
 * @brief force the thread to sleep
 * @param time to wait in milliseconds
 */
void XFThreadPort::delay(uint32_t milliseconds)
{
    msleep(milliseconds);
}


#endif // USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION

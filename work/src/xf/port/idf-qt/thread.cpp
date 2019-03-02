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

// TODO: Implement code for XFThreadPort class

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
}

/**
 * @brief override method from QThread. WARNING : Never call this method
 * it will be automatically called by QThread::start()
 * call the method of the provider
 */
void XFThreadPort::run()
{
    /// call the method passed during the construction of thread
    /// this way must be strange, but no way to make otherwise
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
    //setPriority(priority);
}

/**
 * @brief get priority of the thread
 * @return
 */
XFThreadPriority XFThreadPort::getPriority() const
{
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

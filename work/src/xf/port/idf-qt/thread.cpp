#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION != 0)

#include <assert.h>
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


XFThreadPort::XFThreadPort(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
    _pEntryMethodProvider = pProvider;
    _entryMethod = entryMethod;
    setStackSize(stackSize);
}

void XFThreadPort::run()
{
    run();
}
void XFThreadPort::start()
{
    start();
}

void XFThreadPort::suspend()
{

}

void XFThreadPort::stop()
{
    exit();
}

void XFThreadPort::setPriority(XFThreadPriority priority)
{
    setPriority(priority);
}

XFThreadPriority XFThreadPort::getPriority() const
{
    return XF_THREAD_PRIO_UNKNOWN;
}

void XFThreadPort::delay(uint32_t milliseconds)
{
    msleep(milliseconds);
}


#endif // USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION

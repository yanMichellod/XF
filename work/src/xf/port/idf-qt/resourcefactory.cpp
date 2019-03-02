#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION != 0)

#include <QtGlobal>
#include "thread.h"
#include "trace/trace.h"
#include "default/dispatcher-active.h"
#include "mutex.h"
#include "resourcefactory.h"

///Static Function
// TODO: Implement code for XFResourceFactoryPort class

interface::XFResourceFactory *interface::XFResourceFactory::getInstance()
{
    return XFResourceFactoryPort::getInstance();
}
/**
 * @brief Getter of an instance of interfacec::XFResourceFactory
 */
interface::XFResourceFactory *XFResourceFactoryPort::getInstance()
{
    static interface::XFResourceFactory* FactoryInstance = nullptr;
    if (FactoryInstance == nullptr){
        FactoryInstance = new XFResourceFactoryPort();
    }
    return FactoryInstance;
}

/**
 * @brief Get an instance of the default dispatcher
 * @return pointer to the unique instance of the dispatcher
 */
interface::XFDispatcher *XFResourceFactoryPort::getDefaultDispatcher()
{
    static interface::XFDispatcher* dispatcherInstance = nullptr;
    if(dispatcherInstance == nullptr){
        Trace::out("Create dispatcher...\n---------------------");
        dispatcherInstance = createDispatcher();
    }
    return dispatcherInstance;
}

/**
 * @brief Create Dispatcher. Only call once in this case due to the singleton pattern
 *        Already call in the getDefaultDispatcher()
 * @return pointer to a instance::Dispatcher
 */
interface::XFDispatcher *XFResourceFactoryPort::createDispatcher()
{
    return new XFDispatcherActiveDefault();
}

/**
 * @brief create thread
 * @param pProvider Provider of the method to execute
 * @param entryMethod Method to execute by the tread. It must be an infinite loop.
 * @param threadName Name of the tread
 * @param stackSize Size of the stack
 * @return Pointer to an instance of interface::XFThread
 */
interface::XFThread *XFResourceFactoryPort::createThread(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
    return (interface::XFThread*) new XFThreadPort(pProvider, entryMethod, threadName, stackSize);
}

/**
 * @brief create Mutex
 * @return Pointer to an instance of interface::XFMutex
 */
interface::XFMutex *XFResourceFactoryPort::createMutex()
{
    return new XFMutexPort();
}
#endif // USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION


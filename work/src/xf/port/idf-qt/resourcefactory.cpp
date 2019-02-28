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

interface::XFDispatcher *XFResourceFactoryPort::getDefaultDispatcher()
{
    static interface::XFDispatcher* dispatcherInstance = nullptr;
    if(dispatcherInstance == nullptr){
        Trace::out("Create dispatcher...\n---------------------");
        dispatcherInstance = createDispatcher();
    }
    return dispatcherInstance;
}

interface::XFDispatcher *XFResourceFactoryPort::createDispatcher()
{
    return new XFDispatcherActiveDefault();
}

interface::XFThread *XFResourceFactoryPort::createThread(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
    return (interface::XFThread*) new XFThreadPort(pProvider, entryMethod, threadName, stackSize);
}

interface::XFMutex *XFResourceFactoryPort::createMutex()
{
    return new XFMutexPort();
}
#endif // USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION


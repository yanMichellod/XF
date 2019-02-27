#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION != 0)

#include <QtGlobal>
#include "thread.h"
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
    static interface::XFResourceFactory* instance = nullptr;
    if (instance == nullptr){
        instance = new XFResourceFactoryPort();
    }
    return instance;
}

interface::XFDispatcher *XFResourceFactoryPort::getDefaultDispatcher()
{
}

interface::XFDispatcher *XFResourceFactoryPort::createDispatcher()
{

}

interface::XFThread *XFResourceFactoryPort::createThread(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{

}

interface::XFMutex *XFResourceFactoryPort::createMutex()
{
    return new XFMutexPort();
}
#endif // USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION


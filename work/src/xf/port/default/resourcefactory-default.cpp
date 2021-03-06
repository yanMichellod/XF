#include <config/xf-config.h>

#if (USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION != 0)

#include "resourcefactory-default.h"
#include "mutex-default.h"

//static
interface::XFResourceFactory * interface::XFResourceFactory::getInstance()
{
	return XFResourceFactoryDefault::getInstance();
}

interface::XFResourceFactory * XFResourceFactoryDefault::getInstance(){
	///< Returns a pointer to the unique instance of the XF resource factory.
    static interface::XFResourceFactory* FactoryInstance = nullptr;
    if (FactoryInstance == nullptr){
        FactoryInstance = new XFResourceFactoryDefault();
    }
    return FactoryInstance;
}
interface::XFDispatcher * XFResourceFactoryDefault::getDefaultDispatcher(){
	///< Returns the default dispatcher.
	static interface::XFDispatcher* _mainDispatcher = nullptr;
	if(_mainDispatcher == nullptr){
		_mainDispatcher = createDispatcher();
	}
	return _mainDispatcher;
}
interface::XFDispatcher * XFResourceFactoryDefault::createDispatcher(){
	///< Creates and returns a new dispatcher.
	return new XFDispatcherDefault();
}
interface::XFThread * XFResourceFactoryDefault::createThread(interface::XFThreadEntryPointProvider * pProvider,
											   interface::XFThread::EntryMethodBody entryMethod,
											   const char * threadName,
											   const uint32_t stackSize){
	///< Creates and returns a new thread.
	return nullptr;
}
interface::XFMutex * XFResourceFactoryDefault::createMutex(){
	///< Creates and returns a new mutex.
	return new XFMutexDefault();
}
#endif // USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION

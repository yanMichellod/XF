#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_XF_IMPLEMENTATION != 0)

#include <QCoreApplication>
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"

using interface::XFResourceFactory;

// TODO: Implement code for XF class

void XF::initialize(int timeInterval, int argc, char *argv[])
{
    interface::XFResourceFactory::getInstance()->getDefaultDispatcher();
    interface::XFTimeoutManager::getInstance()->initialize(timeInterval);
    interface::XFTimeoutManager::getInstance()->start();
}

int XF::exec()
{
    getDefaultDispatcher()->execute();
}

int XF::execOnce()
{
    getDefaultDispatcher()->executeOnce();
}

interface::XFDispatcher *XF::getDefaultDispatcher()
{
    return XFResourceFactory::getInstance()->getDefaultDispatcher();
}

#endif // USE_XF_PORT_IDF_QT_XF_IMPLEMENTATION

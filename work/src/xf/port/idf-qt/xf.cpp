#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_XF_IMPLEMENTATION != 0)
#include <QCoreApplication>
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"

using interface::XFResourceFactory;
QCoreApplication* XF::_app = nullptr;
// TODO: Implement code for XF class
/**
 * @brief initialize all object needed to run the application
 * Initialise the timeoutManager and the dispatcher then run the thread to execute the timer
 * @param timeInterval Interval the timer must be initialized
 * @param argc
 * @param argv
 */
void XF::initialize(int timeInterval, int argc, char *argv[])
{
    XF::_app = new QCoreApplication(argc, argv);
    getDefaultDispatcher()->start();
    interface::XFTimeoutManager::getInstance()->initialize(timeInterval);
    interface::XFTimeoutManager::getInstance()->start();
}

/**
 * @brief exec method to make an infinite loop
 * the exec method is called by the QCoreApplication to allow the QT signal/slot to work
 * @return
 */
int XF::exec()
{
    XF::_app->exec();
    return 1;
}

/**
 * @brief execute the dispatcher to dispatch only one event
 * @return
 */
int XF::execOnce()
{
    getDefaultDispatcher()->executeOnce();
    return 1;
}

/**
 * @brief get the default dispatcher
 * @return Pointer to an instance of the dispatcher.
 */
interface::XFDispatcher *XF::getDefaultDispatcher()
{
    return XFResourceFactory::getInstance()->getDefaultDispatcher();
}

#endif // USE_XF_PORT_IDF_QT_XF_IMPLEMENTATION

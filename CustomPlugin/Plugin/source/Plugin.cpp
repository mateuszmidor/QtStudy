/**
 *   @file: Plugin.cpp
 *
 *   @date: Jun 27, 2016
 * @author: Mateusz Midor
 */

#include "Plugin.h"

#include <QtQml/qqml.h>
#include "TunerImpl.h"


/**
 * @name    tunerSingletonFactory
 * @brief   Create an instance of Tuner implementation
 * @param   engine Default owner of the created QObject*
 * @return  Tuner implementation instance
 * @note    QT takes care of not creating more than 1 instance, no need to check if instance already created here
 */
QObject *Plugin::tunerSingletonFactory(QQmlEngine *engine, QJSEngine *) {
    return new TunerImpl((QObject*)engine);
}

/**
 * @name    registerTypes
 * @brief   Register all the types that are to be exposed to QML engine
 */
void Plugin::registerTypes(const char *uri) {
    qmlRegisterSingletonType<Tuner>(uri, 0, 1, "Tuner", &Plugin::tunerSingletonFactory);
//    qmlRegisterType<ChannelList>("ChannelList", 1, 0, "ChannelList", "This type is an interface and can't be created");
}

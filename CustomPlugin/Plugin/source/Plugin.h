/**
 *   @file: Plugin.h
 *
 *   @date: Jun 27, 2016
 * @author: Mateusz Midor
 */

#ifndef CUSTOMPLUGIN_PLUGIN_H_
#define CUSTOMPLUGIN_PLUGIN_H_

#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/QJSEngine>

/**
 * @class   Plugin
 * @brief   Expose Tuner instance to QML engine by means of dynamic library loaded as QT plugin
 * @note    If you "import Plugin 0.1" to access Tuner from QML, the QML engine will search for following dir structure in curr dir:
 *
 *          Plugin
 *          ├── libPlugin.so
 *          └── qmldir
 *
 *          , "qmldir" file contents:
 *          ─────────────────
 *          │ module Plugin │ 
 *          │ plugin Plugin │ 
 *          ─────────────────
 */
class Plugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    static QObject* tunerSingletonFactory(QQmlEngine* engine, QJSEngine* scriptEngine);
    void registerTypes(const char *uri) override;
};

#endif /* CUSTOMPLUGIN_PLUGIN_H_ */

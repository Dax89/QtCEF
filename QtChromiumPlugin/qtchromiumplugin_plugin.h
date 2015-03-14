#ifndef QTCHROMIUMPLUGIN_PLUGIN_H
#define QTCHROMIUMPLUGIN_PLUGIN_H

#include <QQmlExtensionPlugin>

class QtChromiumPluginPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // QTCHROMIUMPLUGIN_PLUGIN_H


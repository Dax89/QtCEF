#include "qtchromiumplugin_plugin.h"
#include "qquickchromiumwebview.h"

#include <qqml.h>

void QtChromiumPluginPlugin::registerTypes(const char *uri)
{
    // @uri QtChromium
    qmlRegisterType<QQuickChromiumWebView>(uri, 1, 0, "ChromiumWebView");
}

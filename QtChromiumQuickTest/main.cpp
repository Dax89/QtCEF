#include <QApplication>
#include <QQmlApplicationEngine>
#include "chromiumcontext.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ChromiumContext* context = ChromiumContext::createInstance(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath(app.applicationDirPath());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    context->doEvents();
    return app.exec();
}

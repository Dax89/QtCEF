#include "mainwindow.h"
#include <QApplication>
#include "chromiumcontext.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ChromiumContext* context = ChromiumContext::createInstance(argc, argv);

    MainWindow w;
    w.show();

    context->doEvents();
    return app.exec();
}

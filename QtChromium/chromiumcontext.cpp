#include "chromiumcontext.h"

ChromiumContext* ChromiumContext::_context = NULL;
QString ChromiumContext::SubProcessPath;

ChromiumContext::ChromiumContext(int argc, char* argv[], QObject *parent): QObject(parent)
{
    this->initCEF(argc, argv);

    this->_timer = new QTimer();
    this->_timer->setInterval(1);
    connect(this->_timer, SIGNAL(timeout()), this, SLOT(processEvents()));
}

ChromiumContext::~ChromiumContext()
{

}

void ChromiumContext::initCEF(int argc, char* argv[])
{
    this->initCEFSettings();
    this->_application = CefRefPtr<ChromiumApplication>(new ChromiumApplication());

    CefMainArgs mainargs(argc, argv);
    int exitcode = CefExecuteProcess(mainargs, this->_application.get(), NULL);

    if(exitcode >= 0)
    {
        qWarning() << Q_FUNC_INFO << "CefExecuteProcess returned" << exitcode;
        return;
    }

    if(!CefInitialize(mainargs, this->_settings, this->_application.get(), NULL))
        qWarning() << Q_FUNC_INFO << "CefInitialize failed";
}

void ChromiumContext::initCEFSettings()
{
    if(ChromiumContext::SubProcessPath.isEmpty())
    {
        QString subprocesspath = QString("%1%2%3").arg(qApp->applicationDirPath(), QDir::separator(), "ChromiumProcess");
        CefString(&this->_settings.browser_subprocess_path).FromASCII(subprocesspath.toUtf8().constData());
    }
    else
        CefString(&this->_settings.browser_subprocess_path).FromASCII(SubProcessPath.toUtf8().constData());

    CefString(&this->_settings.cache_path) = CefString(QStandardPaths::writableLocation(QStandardPaths::CacheLocation).toStdWString());
    CefString(&this->_settings.resources_dir_path) = CefString();
    CefString(&this->_settings.locales_dir_path) = CefString();

    this->_settings.windowless_rendering_enabled = true;
    this->_settings.log_severity = LOGSEVERITY_DISABLE;

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(stopEvents()));
}

void ChromiumContext::processEvents()
{
    CefDoMessageLoopWork();
}

void ChromiumContext::stopEvents()
{
    if(this->_timer->isActive())
        this->_timer->stop();

    CefShutdown();
}

void ChromiumContext::doEvents()
{
    this->_timer->start();
}

ChromiumContext *ChromiumContext::createInstance(int argc, char *argv[])
{
    if(!ChromiumContext::_context)
        ChromiumContext::_context = new ChromiumContext(argc, argv, qApp);

    return ChromiumContext::_context;
}

ChromiumContext *ChromiumContext::instance()
{
    return ChromiumContext::_context;
}


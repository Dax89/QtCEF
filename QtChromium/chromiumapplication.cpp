#include "chromiumapplication.h"
#include <QDebug>

ChromiumApplication::ChromiumApplication()
{
    ChromiumApplication::CreateBrowserDelegates(this->_browserdelegateset);
    ChromiumApplication::CreateRendererDelegates(this->_rendererdelegateset);
}

ChromiumApplication::~ChromiumApplication()
{

}

CefRefPtr<CefBrowserProcessHandler> ChromiumApplication::GetBrowserProcessHandler()
{
    return this;
}

CefRefPtr<CefRenderProcessHandler> ChromiumApplication::GetRenderProcessHandler()
{
    return this;
}

CefRefPtr<CefResourceBundleHandler> ChromiumApplication::GetResourceBundleHandler()
{
    return this;
}

void ChromiumApplication::OnContextInitialized()
{
    BrowserDelegateSet::iterator it = this->_browserdelegateset.begin();

    for(; it != this->_browserdelegateset.end(); it++)
        (*it)->OnContextInitialized(this);
}

void ChromiumApplication::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> commandline)
{
    BrowserDelegateSet::iterator it = this->_browserdelegateset.begin();

    for(; it != this->_browserdelegateset.end(); it++)
        (*it)->OnBeforeChildProcessLaunch(this, commandline);
}

void ChromiumApplication::OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extrainfo)
{
    BrowserDelegateSet::iterator it = this->_browserdelegateset.begin();

    for(; it != this->_browserdelegateset.end(); it++)
        (*it)->OnRenderProcessThreadCreated(this, extrainfo);
}

CefRefPtr<CefLoadHandler> ChromiumApplication::GetLoadHandler()
{
    CefRefPtr<CefLoadHandler> loadhandler;
    RendererDelegateSet::iterator it = this->_rendererdelegateset.begin();

    for(; it != this->_rendererdelegateset.end(); it++)
        loadhandler = (*it)->GetLoadHandler(this);

    return loadhandler;
}

void ChromiumApplication::OnRenderThreadCreated(CefRefPtr<CefListValue> extrainfo)
{
    RendererDelegateSet::iterator it = this->_rendererdelegateset.begin();

    for(; it != this->_rendererdelegateset.end(); it++)
        (*it)->OnRenderThreadCreated(this, extrainfo);
}

void ChromiumApplication::OnWebKitInitialized() /* TODO: Da Verificare */
{
    RendererDelegateSet::iterator it = this->_rendererdelegateset.begin();

    for(; it != this->_rendererdelegateset.end(); it++)
        (*it)->OnWebKitInitialized(this);
}

void ChromiumApplication::OnBrowserCreated(CefRefPtr<CefBrowser> browser)
{
    RendererDelegateSet::iterator it = this->_rendererdelegateset.begin();

    for(; it != this->_rendererdelegateset.end(); it++)
        (*it)->OnBrowserCreated(this, browser);
}

void ChromiumApplication::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser)
{
    RendererDelegateSet::iterator it = this->_rendererdelegateset.begin();

    for(; it != this->_rendererdelegateset.end(); it++)
        (*it)->OnBrowserDestroyed(this, browser);
}

void ChromiumApplication::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    RendererDelegateSet::iterator it = this->_rendererdelegateset.begin();

    for(; it != this->_rendererdelegateset.end(); it++)
        (*it)->OnContextCreated(this, browser, frame, context);
}

void ChromiumApplication::OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    RendererDelegateSet::iterator it = this->_rendererdelegateset.begin();

    for(; it != this->_rendererdelegateset.end(); it++)
        (*it)->OnContextReleased(this, browser, frame, context);
}

void ChromiumApplication::OnUncaughtException(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context, CefRefPtr<CefV8Exception> exception, CefRefPtr<CefV8StackTrace> stacktrace)
{
    RendererDelegateSet::iterator it = this->_rendererdelegateset.begin();

    for(; it != this->_rendererdelegateset.end(); it++)
        (*it)->OnUncaughtException(this, browser, frame, context, exception, stacktrace);
}

void ChromiumApplication::OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefDOMNode> node)
{
    RendererDelegateSet::iterator it = this->_rendererdelegateset.begin();

    //qDebug() << QString::fromStdString(node->GetElementTagName().ToString());

    for(; it != this->_rendererdelegateset.end(); it++)
        (*it)->OnFocusedNodeChanged(this, browser, frame, node);
}

bool ChromiumApplication::OnBeforeNavigation(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRenderProcessHandler::NavigationType navigationtype, bool isredirect)
{
    RendererDelegateSet::iterator it = this->_rendererdelegateset.begin();

    for(; it != this->_rendererdelegateset.end(); it++)
    {
        if((*it)->OnBeforeNavigation(this, browser, frame, request, navigationtype, isredirect))
            return true;
    }

    return false;
}

bool ChromiumApplication::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId sourceprocess, CefRefPtr<CefProcessMessage> message)
{
    bool handled = false;
    RendererDelegateSet::iterator it = this->_rendererdelegateset.begin();

    for(; it != this->_rendererdelegateset.end(); it++)
        handled = (*it)->OnProcessMessageReceived(this, browser, sourceprocess, message);

    return handled;
}

bool ChromiumApplication::GetLocalizedString(int, CefString &)
{
    return false;
}

bool ChromiumApplication::GetDataResource(int, void *&, size_t &)
{
    return false;
}

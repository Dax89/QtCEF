#include "chromiumhandler.h"

namespace
{
    enum ChromiumMenuIds
    {
        CLIENT_ID_SHOW_DEVTOOLS = MENU_ID_USER_FIRST,
    };
}

const char* ChromiumHandler::FocusedNodeChangedMessage = "ChromiumRenderer.FocusedNodeChanged";
int ChromiumHandler::_browsercount = 0;

ChromiumHandler::ChromiumHandler(): _focusoneditablefield(false), _browserid(0), _isclosing(false), _listener(NULL)
{

}

ChromiumHandler::~ChromiumHandler()
{

}

void ChromiumHandler::SetListener(ChromiumHandler::Listener *listener)
{
    this->_listener = listener;
}

bool ChromiumHandler::FocusOnEditableField() const
{
    return this->_focusoneditablefield;
}

CefRefPtr<CefBrowser> ChromiumHandler::GetBrowser() const
{
    return this->_browser;
}

CefRefPtr<CefContextMenuHandler> ChromiumHandler::GetContextMenuHandler()
{
    return this;
}

CefRefPtr<CefDisplayHandler> ChromiumHandler::GetDisplayHandler()
{
    return this;
}

CefRefPtr<CefDownloadHandler> ChromiumHandler::GetDownloadHandler()
{
    return this;
}

CefRefPtr<CefDragHandler> ChromiumHandler::GetDragHandler()
{
    return this;
}

CefRefPtr<CefGeolocationHandler> ChromiumHandler::GetGeolocationHandler()
{
    return this;
}

CefRefPtr<CefKeyboardHandler> ChromiumHandler::GetKeyboardHandler()
{
    return this;
}

CefRefPtr<CefFocusHandler> ChromiumHandler::GetFocusHandler()
{
    return this;
}

CefRefPtr<CefLifeSpanHandler> ChromiumHandler::GetLifeSpanHandler()
{
    return this;
}

CefRefPtr<CefLoadHandler> ChromiumHandler::GetLoadHandler()
{
    return this;
}

CefRefPtr<CefRenderHandler> ChromiumHandler::GetRenderHandler()
{
    return this;
}

CefRefPtr<CefRequestHandler> ChromiumHandler::GetRequestHandler()
{
    return this;
}

bool ChromiumHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId sourceprocess, CefRefPtr<CefProcessMessage> message)
{
    CefString messagename = message->GetName();

    if(messagename == ChromiumHandler::FocusedNodeChangedMessage)
    {
        this->_focusoneditablefield = message->GetArgumentList()->GetBool(0);
        return true;
    }

    bool handled = false;
    ProcessMessageDelegateSet::iterator it = this->_processmessagedelegateset.begin();

    for(; it != this->_processmessagedelegateset.end(); it++)
        handled = (*it)->OnProcessMessageReceived(this, browser, sourceprocess, message);

    return handled;
}

void ChromiumHandler::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame>, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model)
{
    if((params->GetTypeFlags() & (CM_TYPEFLAG_PAGE | CM_TYPEFLAG_FRAME)) != 0)
    {
      int count = model->GetCount();

      for(int i = count - 1; i >=0; i--)
      {
          if (model->GetCommandIdAt(i) != MENU_ID_VIEW_SOURCE)
              model->RemoveAt(i);
      }

      /* FIXME: Serve Veramente?
      CefString devtoolsurl = browser->GetHost()->GetDevToolsURL(true);
      model->AddItem(CLIENT_ID_SHOW_DEVTOOLS, "&Show DevTools");

      if (devtoolsurl.empty() || _opendevtoolsurls.find(devtoolsurl) != _opendevtoolsurls.end())
            model->SetEnabled(CLIENT_ID_SHOW_DEVTOOLS, false);
            */
    }
}

bool ChromiumHandler::OnContextMenuCommand(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, int commandid, CefContextMenuHandler::EventFlags eventflags)
{
    switch(commandid)
    {
        case CLIENT_ID_SHOW_DEVTOOLS:
            //this->ShowDevTools(browser);
            break; //return true;

        default:  /* Allow default handling, if any */
            break;
     }

    return false;
}

bool ChromiumHandler::OnConsoleMessage(CefRefPtr<CefBrowser>, const CefString&, const CefString&, int)
{
    return false;
}

void ChromiumHandler::OnBeforeDownload(CefRefPtr<CefBrowser>, CefRefPtr<CefDownloadItem>, const CefString&, CefRefPtr<CefBeforeDownloadCallback>)
{
    CEF_REQUIRE_UI_THREAD();
}

void ChromiumHandler::OnDownloadUpdated(CefRefPtr<CefBrowser>, CefRefPtr<CefDownloadItem>, CefRefPtr<CefDownloadItemCallback>)
{
    CEF_REQUIRE_UI_THREAD();
}

bool ChromiumHandler::OnDragEnter(CefRefPtr<CefBrowser>, CefRefPtr<CefDragData>, CefDragHandler::DragOperationsMask mask)
{
    CEF_REQUIRE_UI_THREAD();

    /* Forbid dragging of link URLs */
    if(mask & DRAG_OPERATION_LINK)
        return true;

    return false;
}

bool ChromiumHandler::OnRequestGeolocationPermission(CefRefPtr<CefBrowser>, const CefString&, int, CefRefPtr<CefGeolocationCallback> callback)
{
    /* Allow geolocation access from all websites */
    callback->Continue(true);
    return true;
}

bool ChromiumHandler::OnPreKeyEvent(CefRefPtr<CefBrowser>, const CefKeyEvent& event, XEvent*, bool*)
{
    return false;
}

bool ChromiumHandler::OnSetFocus(CefRefPtr<CefBrowser> browser, CefFocusHandler::FocusSource source)
{
    return false;
}

bool ChromiumHandler::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame>, const CefString&, const CefString&, const CefPopupFeatures&, CefWindowInfo&, CefRefPtr<CefClient>&, CefBrowserSettings&, bool*)
{
    if(browser->GetHost()->IsWindowRenderingDisabled())
        return true; /* Cancel popups in off-screen rendering mode */

    return false;
}

void ChromiumHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();

    if(!this->_browser.get())
    {
        this->_browser = browser; /* We need to keep the main child window, but not popup windows */
        this->_browserid = browser->GetIdentifier();
    }
    else if(browser->IsPopup())
        _popupbrowsers.push_back(browser); /* Add to the list of popup browsers */

    this->_browsercount++;
}

bool ChromiumHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();

    /*
     * Closing the main window requires special handling. See the DoClose()
     * documentation in the CEF header for a detailed destription of this process
     */

    if (this->_browserid == browser->GetIdentifier())
    {
        //FIXME: browser->GetHost(); /* Notify the browser that the parent window is about to close. */
        this->_isclosing = true; /* Set a flag to indicate that the window close should be allowed */
    }

    return false; /* Allow the close. For windowed browsers this will result in the OS close event being sent */
}

void ChromiumHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();

    if (this->_browserid == browser->GetIdentifier())
        this->_browser = NULL;/* Free the browser pointer so that the browser can be destroyed */
    else if (browser->IsPopup())
    {
        // Remove the record for DevTools popup windows.
        std::set<CefString>::iterator popupit = _opendevtoolsurls.find(browser->GetMainFrame()->GetURL());

        if (popupit != _opendevtoolsurls.end())
            _opendevtoolsurls.erase(popupit);

        // Remove from the browser popup list.
        BrowserList::iterator it = this->_popupbrowsers.begin();

        for (; it != this->_popupbrowsers.end(); ++it)
        {
            if((*it)->IsSame(browser))
            {
                this->_popupbrowsers.erase(it);
                break;
            }
        }
    }

    //if(--this->_browsercount == 0)
    //NotifyAllBrowserClosed(); / TODO: Da implementare?
}

void ChromiumHandler::OnLoadingStateChange(CefRefPtr<CefBrowser>, bool isloading, bool cangoback, bool cangoforward)
{
    CEF_REQUIRE_UI_THREAD();
    this->SetNavState(cangoback, cangoforward);
}

void ChromiumHandler::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
{
    CEF_REQUIRE_UI_THREAD();

    if((this->_browserid == browser->GetIdentifier()) && frame->IsMain() && this->_listener)
        this->_listener->OnLoadStart(frame);
}

void ChromiumHandler::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpstatuscode)
{
    CEF_REQUIRE_UI_THREAD();

    if((this->_browserid == browser->GetIdentifier()) && frame->IsMain() && this->_listener)
        this->_listener->OnLoadEnd(frame, httpstatuscode);
}

void ChromiumHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorcode, const CefString &errortext, const CefString &failedurl)
{
    CEF_REQUIRE_UI_THREAD();

    if((this->_browserid == browser->GetIdentifier()) && frame->IsMain() && this->_listener)
        this->_listener->OnLoadError(frame, errorcode, errortext, failedurl);
}

bool ChromiumHandler::GetViewRect(CefRefPtr<CefBrowser>, CefRect &rect)
{
    if(this->_listener)
        return this->_listener->GetViewRect(rect);

    return false;
}

void ChromiumHandler::OnPaint(CefRefPtr<CefBrowser>, CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList &dirtyrects, const void *buffer, int width, int height)
{
    CEF_REQUIRE_UI_THREAD();

    if(this->_listener)
        this->_listener->OnPaint(type, dirtyrects, buffer, width, height);
}

void ChromiumHandler::OnCursorChange(CefRefPtr<CefBrowser>, unsigned long, CefRenderHandler::CursorType type, const CefCursorInfo &customcursorinfo)
{
    CEF_REQUIRE_UI_THREAD();

    if(this->_listener)
        this->_listener->OnCursorChange(type, customcursorinfo);
}

CefRefPtr<CefResourceHandler> ChromiumHandler::GetResourceHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request)
{
    return NULL;
}

bool ChromiumHandler::OnQuotaRequest(CefRefPtr<CefBrowser> browser, const CefString &originurl, int64 newsize, CefRefPtr<CefQuotaCallback> callback)
{   
    static int MAX_SIZE = 1024 * 1024 * 20; /* 20MB */

    callback->Continue(newsize <= MAX_SIZE);
    return true;
}

void ChromiumHandler::OnProtocolExecution(CefRefPtr<CefBrowser> browser, const CefString &url, bool &allowosexecution)
{

}

void ChromiumHandler::OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser, CefRequestHandler::TerminationStatus status)
{
    /*
    // Load the startup URL if that's not the website that we terminated on.
    CefRefPtr<CefFrame> frame = browser->GetMainFrame();
    CefString url = frame->GetURL();
    std::string startupURL = GetStartupURL();

    if (url.find(startupURL) != 0)
      frame->LoadURL(startupURL);
    */
}

bool ChromiumHandler::OnBeforePluginLoad(CefRefPtr<CefBrowser>, const CefString&, const CefString&, CefRefPtr<CefWebPluginInfo>)
{
    return false;  // Return true to block loading of the plugin.
}

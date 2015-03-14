#ifndef CHROMIUMHANDLER_H
#define CHROMIUMHANDLER_H

#include <set>
#include <list>
#include <QString>
#include <QDebug>
#include "include/cef_client.h"
#include "include/base/cef_lock.h"
#include "include/wrapper/cef_helpers.h"
#include "chromiummessageevent.h"

class ChromiumHandler: public CefClient, public CefContextMenuHandler, public CefDisplayHandler, public CefDownloadHandler, public CefDragHandler, public CefGeolocationHandler,
                       public CefKeyboardHandler, public CefFocusHandler, public CefLifeSpanHandler, public CefLoadHandler, public CefRenderHandler, public CefRequestHandler
{
    public:
        class ProcessMessageDelegate: public CefBase
        {
            public:
                virtual bool OnProcessMessageReceived(CefRefPtr<ChromiumHandler>, CefRefPtr<CefBrowser>, CefProcessId, CefRefPtr<CefProcessMessage>) { return false; }
        };

        typedef std::set< CefRefPtr<ProcessMessageDelegate> > ProcessMessageDelegateSet;

    public:
        class Listener
        {
            public:
                virtual ~Listener() { }
                virtual void OnAddressChange(const QString& url) = 0;
                virtual void OnTitleChange(const QString& title) = 0;
                virtual void SetLoading(bool isloading) = 0;
                virtual void SetNavState(bool cangoback, bool cangoforward) = 0;
                virtual void OnAfterCreated() = 0;
                virtual void OnGotFocus() = 0;
                virtual bool GetViewRect(CefRect &rect) = 0;
                virtual void OnPaint(CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList &dirtyrects, const void *buffer, int width, int height) = 0;
                virtual void OnMessageEvent(ChromiumMessageEvent* e) = 0;
        };

    public:
        ChromiumHandler();
        ~ChromiumHandler();

    public:
        void SetListener(Listener* listener);
        CefRefPtr<CefBrowser> GetBrowser() const;

    protected:
        void SetLoading(bool isloading);  /* *** Qt Side *** */
        void SetNavState(bool cangoback, bool cangoforward);  /* *** Qt Side *** */

    public: /* CefClient Methods */
        virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler();
        virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler();
        virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler();
        virtual CefRefPtr<CefDragHandler> GetDragHandler();
        virtual CefRefPtr<CefGeolocationHandler> GetGeolocationHandler();
        virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler();
        virtual CefRefPtr<CefFocusHandler> GetFocusHandler();
        virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler();
        virtual CefRefPtr<CefLoadHandler> GetLoadHandler();
        virtual CefRefPtr<CefRenderHandler> GetRenderHandler();
        virtual CefRefPtr<CefRequestHandler> GetRequestHandler();
        virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId sourceprocess, CefRefPtr<CefProcessMessage> message);

    public: /* CefContextMenuHandler Methods */
        virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame>, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model);
        virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, int commandid, EventFlags eventflags);

    public: /* CefDisplayHandler Methods */
        virtual void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url); /* *** Qt Side *** */
        virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title); /* *** Qt Side *** */
        virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString&, int);

    public: /* CefDownloadHandler Methods */
        virtual void OnBeforeDownload(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> downloaditem, const CefString&, CefRefPtr<CefBeforeDownloadCallback>);
        virtual void OnDownloadUpdated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem>, CefRefPtr<CefDownloadItemCallback>);

    public: /* CefDragHandler Methods */
        virtual bool OnDragEnter(CefRefPtr<CefBrowser>, CefRefPtr<CefDragData>, CefDragHandler::DragOperationsMask mask);

    public: /* CefGeolocationHandler Methods */
        virtual bool OnRequestGeolocationPermission(CefRefPtr<CefBrowser> browser, const CefString&, int, CefRefPtr<CefGeolocationCallback> callback);

    public: /* CefKeyboardHandler Methods */
        virtual bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent&event, CefEventHandle, bool*);

    public: /* CefFocusHandler Methods */
        virtual bool OnSetFocus(CefRefPtr<CefBrowser> browser, FocusSource source);
        virtual void OnGotFocus(CefRefPtr<CefBrowser> browser);
        virtual void OnTakeFocus(CefRefPtr<CefBrowser> browser, bool next);

    public: /* CefLifeSpanHandler Methods */
        virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& targeturl, const CefString& targetframename, const CefPopupFeatures& popupfeatures, CefWindowInfo& windowinfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, bool*);
        virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser);
        virtual bool DoClose(CefRefPtr<CefBrowser> browser);
        virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser);

    public: /* CefLoadHandler Methods */
        virtual void OnLoadingStateChange(CefRefPtr<CefBrowser>, bool isloading, bool cangoback, bool cangoforward);
        virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame);
        virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpstatuscode);
        virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorcode, const CefString& errortext, const CefString& failedurl);

    public: /* CefRenderHandler Methods */
        virtual bool GetViewRect(CefRefPtr<CefBrowser>, CefRect &rect);
        virtual void OnPaint(CefRefPtr<CefBrowser>, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height);

    public: /* CefRequestHandler Methods */
          virtual CefRefPtr<CefResourceHandler> GetResourceHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request);
          virtual bool OnQuotaRequest(CefRefPtr<CefBrowser> browser, const CefString& originurl, int64 newsize, CefRefPtr<CefQuotaCallback> callback);
          virtual void OnProtocolExecution(CefRefPtr<CefBrowser> browser, const CefString& url, bool& allowosexecution);
          virtual void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser, TerminationStatus status);
          virtual bool OnBeforePluginLoad(CefRefPtr<CefBrowser> browser, const CefString&, const CefString&, CefRefPtr<CefWebPluginInfo>);

    protected:
         typedef std::list< CefRefPtr<CefBrowser> > BrowserList;

    private:
        static const char* FocusedNodeChangedMessage;
        static int _browsercount; /* Number of currently existing browser windows. The application will exit when the number of windows reaches 0. */

    private:
        ProcessMessageDelegateSet _processmessagedelegateset;
        bool _focusoneditablefield;
        int _lockvalue;

    protected:
        int _browserid; /* The child browser id */
        bool _isclosing;
        CefRefPtr<CefBrowser> _browser; /* The child browser window */
        Listener* _listener; /* The listener interface */
        BrowserList _popupbrowsers; /* List of any popup browser windows. Only accessed on the CEF UI thread. */
        std::set<CefString> _opendevtoolsurls; /* List of open DevTools URLs if not using an external browser window */

    IMPLEMENT_REFCOUNTING(ChromiumHandler)
};

#endif // CHROMIUMHANDLER_H

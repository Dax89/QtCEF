#ifndef CHROMIUMAPPLICATION_H
#define CHROMIUMAPPLICATION_H

#include <set>
#include <include/cef_app.h>

class ChromiumApplication: public CefApp, public CefBrowserProcessHandler, public CefRenderProcessHandler, public CefResourceBundleHandler
{
    public:
        class BrowserDelegate: public CefBase
        {
            public:
                virtual void OnContextInitialized(CefRefPtr<ChromiumApplication>) { }
                virtual void OnBeforeChildProcessLaunch(CefRefPtr<ChromiumApplication>, CefRefPtr<CefCommandLine>) { }
                virtual void OnRenderProcessThreadCreated(CefRefPtr<ChromiumApplication>, CefRefPtr<CefListValue>) { }
        };

        typedef std::set< CefRefPtr<BrowserDelegate> > BrowserDelegateSet;

    public:
        class RendererDelegate: public CefBase
        {
            public:
                virtual CefRefPtr<CefLoadHandler> GetLoadHandler(CefRefPtr<ChromiumApplication>) { return NULL; }
                virtual void OnRenderThreadCreated(CefRefPtr<ChromiumApplication>, CefRefPtr<CefListValue>) { }
                virtual void OnWebKitInitialized(CefRefPtr<ChromiumApplication>) { }
                virtual void OnBrowserCreated(CefRefPtr<ChromiumApplication>, CefRefPtr<CefBrowser>) { }
                virtual void OnBrowserDestroyed(CefRefPtr<ChromiumApplication>, CefRefPtr<CefBrowser>) { }
                virtual void OnContextCreated(CefRefPtr<ChromiumApplication>, CefRefPtr<CefBrowser>, CefRefPtr<CefFrame>, CefRefPtr<CefV8Context>) { }
                virtual void OnContextReleased(CefRefPtr<ChromiumApplication>, CefRefPtr<CefBrowser>, CefRefPtr<CefFrame>, CefRefPtr<CefV8Context>) { }
                virtual void OnUncaughtException(CefRefPtr<ChromiumApplication>, CefRefPtr<CefBrowser>, CefRefPtr<CefFrame>, CefRefPtr<CefV8Context>, CefRefPtr<CefV8Exception>, CefRefPtr<CefV8StackTrace>) { }
                virtual void OnFocusedNodeChanged(CefRefPtr<ChromiumApplication>, CefRefPtr<CefBrowser>, CefRefPtr<CefFrame>, CefRefPtr<CefDOMNode>) { }
                virtual bool OnBeforeNavigation(CefRefPtr<ChromiumApplication>, CefRefPtr<CefBrowser>, CefRefPtr<CefFrame>, CefRefPtr<CefRequest>, cef_navigation_type_t, bool) { return false; }
                virtual bool OnProcessMessageReceived(CefRefPtr<ChromiumApplication>, CefRefPtr<CefBrowser>, CefProcessId, CefRefPtr<CefProcessMessage>) { return false; }
        };

        typedef std::set< CefRefPtr<RendererDelegate> > RendererDelegateSet;

    public:
        ChromiumApplication();
        ~ChromiumApplication();

    private: /* Defined in chromiumapplicationdelegates.cpp */
        static void CreateBrowserDelegates(BrowserDelegateSet& browserdelegateset);
        static void CreateRendererDelegates(RendererDelegateSet& rendererdelegateset);
        static void RegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar, std::vector<CefString>& cookiable_schemes);

    public:
        virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler();
        virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler();
        virtual CefRefPtr<CefResourceBundleHandler> GetResourceBundleHandler();

    public: /* CefBrowserProcessHandler Members */
        virtual void OnContextInitialized();
        virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> commandline);
        virtual void OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extrainfo);

    public: /* CefRenderProcessHandler Methods */
        CefRefPtr<CefLoadHandler> GetLoadHandler();
        void OnRenderThreadCreated(CefRefPtr<CefListValue> extrainfo);
        void OnWebKitInitialized();
        void OnBrowserCreated(CefRefPtr<CefBrowser> browser);
        void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser);
        void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);
        void OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);
        void OnUncaughtException(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context, CefRefPtr<CefV8Exception> exception, CefRefPtr<CefV8StackTrace> stacktrace);
        void OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefDOMNode> node);
        bool OnBeforeNavigation(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, NavigationType navigationtype, bool isredirect);
        bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId sourceprocess, CefRefPtr<CefProcessMessage> message);

    public: /* CefResourceBundleHandler Methods */
        virtual bool GetLocalizedString(int, CefString&);
        virtual bool GetDataResource(int, void*&, size_t&);

    private:
        BrowserDelegateSet _browserdelegateset;
        RendererDelegateSet _rendererdelegateset;

    IMPLEMENT_REFCOUNTING(ChromiumApplication)
};

#endif // CHROMIUMAPPLICATION_H

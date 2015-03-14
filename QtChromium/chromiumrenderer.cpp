#include "chromiumrenderer.h"
#include <include/cef_dom.h>
#include <QDebug>

namespace ChromiumRenderer
{
    const char FocusedNodeChangedMessage[] = "ChromiumRenderer.FocusedNodeChanged";

    class ChromiumRendererDelegates: public ChromiumApplication::RendererDelegate
    {
        public:
            ChromiumRendererDelegates(): ChromiumApplication::RendererDelegate(), _lastnodeiseditable(false)
            {

            }

            virtual void OnFocusedNodeChanged(CefRefPtr<ChromiumApplication> app, CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefDOMNode> node)
            {
                bool iseditable = (node.get()) && node->IsEditable();

                if(iseditable && !this->_lastnodeiseditable)
                {
                    // Notify the browser of the change in focused element type
                    this->_lastnodeiseditable = iseditable;

                    CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(FocusedNodeChangedMessage);
                    message->GetArgumentList()->SetBool(0, iseditable);
                    browser->SendProcessMessage(PID_BROWSER, message);
                }
            }

        private:
            bool _lastnodeiseditable;

        IMPLEMENT_REFCOUNTING(ChromiumRendererDelegates)
    };

    void CreateRendererDelegates(ChromiumApplication::RendererDelegateSet &delegates)
    {
        delegates.insert(new ChromiumRendererDelegates());
    }
 }

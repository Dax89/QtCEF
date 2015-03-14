#include "chromiumhandler.h"

void ChromiumHandler::SetLoading(bool isloading)
{
    if(!this->_listener)
        return;

    this->_listener->SetLoading(isloading);
}

void ChromiumHandler::SetNavState(bool cangoback, bool cangoforward)
{
    if(!this->_listener)
        return;

    this->_listener->SetNavState(cangoback, cangoforward);
}

void ChromiumHandler::OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString &url)
{
    CEF_REQUIRE_UI_THREAD();

    if(!this->_listener)
        return;

    if((this->_browserid == browser->GetIdentifier()) && frame->IsMain())
        this->_listener->OnAddressChange(QString::fromStdString(url.ToString()));
}

void ChromiumHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title)
{
    CEF_REQUIRE_UI_THREAD();

    if(!this->_listener)
        return;

    if(this->_browserid == browser->GetIdentifier())
        this->_listener->OnTitleChange(QString::fromStdString(title.ToString()));
}

#include "chromiumhandler.h"

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

void ChromiumHandler::OnFaviconURLChange(CefRefPtr<CefBrowser> browser, const std::vector<CefString> &iconurls)
{
    CEF_REQUIRE_UI_THREAD();

    if(!this->_listener)
        return;

    if(this->_browserid == browser->GetIdentifier())
        this->_listener->OnFaviconChange(QUrl(QString::fromStdString(iconurls.at(0).ToString())));
}

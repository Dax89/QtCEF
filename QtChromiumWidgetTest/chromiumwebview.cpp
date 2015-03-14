#include "chromiumwebview.h"

ChromiumWebView::ChromiumWebView(QWidget *parent) : QGLWidget(parent), _needsrepaint(false)
{
    this->_handler = CefRefPtr<ChromiumHandler>(new ChromiumHandler());
    this->setFocusPolicy(Qt::StrongFocus);
}

ChromiumWebView::~ChromiumWebView()
{

}

void ChromiumWebView::createBrowser()
{
    CEF_REQUIRE_UI_THREAD();

    CefWindowInfo windowinfo;
    CefBrowserSettings browsersettings;

    windowinfo.SetAsWindowless(this->winId(), false);
    this->_handler->SetListener(this);

    CefBrowserHost::CreateBrowserSync(windowinfo, this->_handler.get(), "http://www.google.com", browsersettings, NULL);
}

CefRefPtr<CefBrowser> ChromiumWebView::GetBrowser() const
{
    CefRefPtr<CefBrowser> browser;

    if (this->_handler.get())
        browser = this->_handler->GetBrowser();

    return browser;
}

void ChromiumWebView::OnAddressChange(const QString &url)
{

}

void ChromiumWebView::OnTitleChange(const QString &title)
{

}

void ChromiumWebView::SetLoading(bool isloading)
{

}

void ChromiumWebView::SetNavState(bool cangoback, bool cangoforward)
{

}

void ChromiumWebView::OnAfterCreated()
{

}

void ChromiumWebView::OnGotFocus()
{
    this->setFocus();
}

bool ChromiumWebView::GetViewRect(CefRect &rect)
{
    rect.Set(0, 0, this->width(), this->height());
    return true;
}

void ChromiumWebView::OnPaint(CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList &dirtyrects, const void *buffer, int width, int height)
{
    if(type != PET_VIEW)
        return;

    qDebug() << Q_FUNC_INFO << width << "x" << height;
    //this->_image = QImage(reinterpret_cast<const uchar*>(buffer), width, height, QImage::format_);
    this->update();
}

void ChromiumWebView::OnMessageEvent(ChromiumMessageEvent *e)
{
    qApp->postEvent(this, e, Qt::HighEventPriority);
}

void ChromiumWebView::focusOutEvent(QFocusEvent *)
{
    /*
    qDebug() << Q_FUNC_INFO;
    CefRefPtr<CefBrowser> browser = this->GetBrowser();

    Platform platform;
    browser->GetHost()->SetFocus(false);
    platform.setFocus(browser->GetHost()->GetWindowHandle(), false);
    browser->GetHost()->SetFocus(false);
    */
}

void ChromiumWebView::paintEvent(QPaintEvent *)
{
    qDebug() << Q_FUNC_INFO << this->_image.isNull();

    QPainter painter(this);
    painter.drawImage(0, 0, this->_image);
    this->_needsrepaint = false;
}

void ChromiumWebView::resizeEvent(QResizeEvent *)
{
    CefRefPtr<CefBrowser> browser = this->GetBrowser();

    if(browser.get())
        browser->GetHost()->WasResized();
}

void ChromiumWebView::showEvent(QShowEvent *)
{
    this->createBrowser();
}

void ChromiumWebView::closeEvent(QCloseEvent *)
{
    CefRefPtr<CefBrowser> browser = this->GetBrowser();

    if(browser.get())
        browser->GetHost()->CloseBrowser(false);
}

void ChromiumWebView::load(const QUrl &url)
{
    CefRefPtr<CefBrowser> browser = this->GetBrowser();

    if(browser.get())
        browser->GetMainFrame()->LoadURL(url.toString().toStdWString());
}

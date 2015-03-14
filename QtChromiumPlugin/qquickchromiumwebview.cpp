#include "qquickchromiumwebview.h"

QQuickChromiumWebView::QQuickChromiumWebView(QQuickItem *webview): QQuickItem(webview), _buffer(NULL), _texture(NULL)
{
    this->setFlag(QQuickItem::ItemHasContents);
    this->setFlag(QQuickItem::ItemIsFocusScope);
    this->setFlag(QQuickItem::ItemAcceptsInputMethod);

    this->setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton | Qt::MiddleButton);
    this->forceActiveFocus();

    this->_handler = CefRefPtr<ChromiumHandler>(new ChromiumHandler());

    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(onWindowChanged(QQuickWindow*)));
    connect(this, SIGNAL(widthChanged()), this, SLOT(onResize()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(onResize()));
}

QQuickChromiumWebView::~QQuickChromiumWebView()
{

}

QString QQuickChromiumWebView::url()
{
    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();
    return QString::fromStdWString(browser->GetMainFrame()->GetURL().ToWString());
}

void QQuickChromiumWebView::setUrl(const QString &url)
{
    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();
    browser->GetMainFrame()->LoadURL(CefString(url.toStdWString()));
}

void QQuickChromiumWebView::createBrowser()
{
    CefWindowInfo windowinfo;
    CefBrowserSettings browsersettings;

    windowinfo.SetAsWindowless(this->window()->winId(), false);
    this->_handler->SetListener(this);
    CefBrowserHost::CreateBrowserSync(windowinfo, this->_handler.get(), "https://www.google.it", browsersettings, NULL);
}

void QQuickChromiumWebView::OnAddressChange(const QString &url)
{
    emit urlChanged();
}

void QQuickChromiumWebView::OnTitleChange(const QString &title)
{

}

void QQuickChromiumWebView::SetLoading(bool isloading)
{

}

void QQuickChromiumWebView::SetNavState(bool cangoback, bool cangoforward)
{

}

void QQuickChromiumWebView::OnAfterCreated()
{
    qDebug() << Q_FUNC_INFO;
}

void QQuickChromiumWebView::OnTakeFocus()
{

}

void QQuickChromiumWebView::OnGotFocus()
{

}

bool QQuickChromiumWebView::GetViewRect(CefRect &rect)
{
    QQuickWindow* window = this->window();

    rect.Set(window->x(), window->y(), this->width(), this->height());
    return true;
}

void QQuickChromiumWebView::OnPaint(CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList &dirtyrects, const void *buffer, int width, int height)
{
    if(type != PET_VIEW)
        return;

    this->_buffer = buffer;
    this->_texwidth = width;
    this->_texheight = height;
    this->update();
}

void QQuickChromiumWebView::OnMessageEvent(ChromiumMessageEvent *e)
{
    qDebug() << Q_FUNC_INFO << e->name();
}

void QQuickChromiumWebView::focusInEvent(QFocusEvent *focusevent)
{
    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();
    browser->GetHost()->SendFocusEvent(true);
}

void QQuickChromiumWebView::focusOutEvent(QFocusEvent *focusevent)
{
    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();
    browser->GetHost()->SendFocusEvent(false);
}

void QQuickChromiumWebView::mousePressEvent(QMouseEvent *mouseevent)
{
    CefBrowserHost::MouseButtonType mbt;
    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();

    CefMouseEvent cefmouseevent;
    cefmouseevent.x = mouseevent->x();
    cefmouseevent.y = mouseevent->y();

    if(mouseevent->button() == Qt::LeftButton)
    {
        this->forceActiveFocus();
        mbt = MBT_LEFT;
    }
    else if(mouseevent->button() == Qt::RightButton)
        mbt = MBT_RIGHT;
    else if(mouseevent->button() == Qt::MiddleButton)
        mbt = MBT_MIDDLE;
    else
        return;

    browser->GetHost()->SendMouseClickEvent(cefmouseevent, mbt, false, 1);
}

void QQuickChromiumWebView::mouseReleaseEvent(QMouseEvent *mouseevent)
{
    CefBrowserHost::MouseButtonType mbt;
    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();

    CefMouseEvent cefmouseevent;
    cefmouseevent.x = mouseevent->x();
    cefmouseevent.y = mouseevent->y();

    if(mouseevent->button() == Qt::LeftButton)
        mbt = MBT_LEFT;
    else if(mouseevent->button() == Qt::RightButton)
        mbt = MBT_RIGHT;
    else if(mouseevent->button() == Qt::MiddleButton)
        mbt = MBT_MIDDLE;
    else
        return;

    browser->GetHost()->SendMouseClickEvent(cefmouseevent, mbt, true, 1);
}

void QQuickChromiumWebView::keyPressEvent(QKeyEvent *keyevent)
{
    qDebug() << Q_FUNC_INFO;

    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();

    CefKeyEvent cefkeyevent;
    cefkeyevent.type = KEYEVENT_CHAR;
    cefkeyevent.character = keyevent->text()[0].toLatin1();

    browser->GetHost()->SendKeyEvent(cefkeyevent);
}

QSGNode *QQuickChromiumWebView::updatePaintNode(QSGNode *oldnode, QQuickItem::UpdatePaintNodeData *)
{
    if(!this->_buffer)
        return NULL;

    QSGSimpleTextureNode* n = static_cast<QSGSimpleTextureNode*>(oldnode);

    if(!n)
    {
        this->_texture = this->renewTexture();

        n = new QSGSimpleTextureNode();
        n->setRect(this->boundingRect());
        n->setTexture(this->_texture);
    }
    else
    {
        this->_texture = this->renewTexture();
        n->markDirty(QSGNode::DirtyMaterial | QSGNode::DirtyGeometry);
        n->setRect(this->boundingRect());
        n->setTexture(this->_texture);
    }

    return n;
}

QSGTexture *QQuickChromiumWebView::renewTexture()
{
    if(this->_texture)
    {
        GLuint tex = this->_texture->textureId();
        delete this->_texture;
        glDeleteTextures(1, &tex);
    }

    GLuint tex;
    glGenTextures(1, &tex);

    QSGTexture* texture = this->window()->createTextureFromId(tex, QSize(this->_texwidth, this->_texheight));
    texture->bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_texwidth, this->_texheight, 0, GL_BGRA, GL_UNSIGNED_BYTE, this->_buffer);

    return texture;
}

void QQuickChromiumWebView::onWindowChanged(QQuickWindow *window)
{
    if(!window)
        return;

    this->createBrowser();
}

void QQuickChromiumWebView::onResize()
{
    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();
    browser->GetHost()->WasResized();
}

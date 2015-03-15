#include "qquickchromiumwebview.h"

QQuickChromiumWebView::QQuickChromiumWebView(QQuickItem *webview): QQuickItem(webview), _cangoback(false), _cangoforward(false), _loading(false), _buffer(NULL), _texture(NULL)
{
    this->setFlag(QQuickItem::ItemHasContents);
    this->setFlag(QQuickItem::ItemIsFocusScope);
    this->setFlag(QQuickItem::ItemAcceptsInputMethod);

    this->setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton | Qt::MiddleButton);
    this->setAcceptHoverEvents(true);
    this->forceActiveFocus();

    this->_handler = CefRefPtr<ChromiumHandler>(new ChromiumHandler());

    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(onWindowChanged(QQuickWindow*)));
    connect(this, SIGNAL(widthChanged()), this, SLOT(onResize()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(onResize()));
}

QQuickChromiumWebView::~QQuickChromiumWebView()
{

}

bool QQuickChromiumWebView::loading() const
{
    return this->_loading;
}

bool QQuickChromiumWebView::canGoBack() const
{
    return this->_cangoback;
}

bool QQuickChromiumWebView::canGoForward() const
{
    return this->_cangoforward;
}

QString QQuickChromiumWebView::title() const
{
    return this->_title;
}

QString QQuickChromiumWebView::url() const
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

void QQuickChromiumWebView::OnAddressChange(const QString &)
{
    emit urlChanged();
}

void QQuickChromiumWebView::OnTitleChange(const QString &title)
{
    this->_title = title;

    emit titleChanged();
}

void QQuickChromiumWebView::SetLoading(bool isloading)
{
    if(this->_loading == isloading)
        return;

    this->_loading = isloading;
    emit loadingChanged();
}

void QQuickChromiumWebView::SetNavState(bool cangoback, bool cangoforward)
{
    if(this->_cangoback != cangoback)
    {
        this->_cangoback = cangoback;
        emit canGoBackChanged();
    }

    if(this->_cangoforward != cangoforward)
    {
        this->_cangoforward = cangoforward;
        emit canGoForwardChanged();
    }
}

void QQuickChromiumWebView::OnAfterCreated()
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

void QQuickChromiumWebView::OnCursorChange(CefRenderHandler::CursorType type, const CefCursorInfo&)
{
    switch(type)
    {
        case CT_CROSS:
            this->setCursor(Qt::CrossCursor);
            break;

        case CT_IBEAM:
            this->setCursor(Qt::IBeamCursor);
            break;

        case CT_WAIT:
            this->setCursor(Qt::WaitCursor);
            break;

        case CT_PROGRESS:
            this->setCursor(Qt::BusyCursor);
            break;

        case CT_HAND:
            this->setCursor(Qt::PointingHandCursor);
            break;

        case CT_GRAB:
            this->setCursor(Qt::OpenHandCursor);
            break;

        case CT_GRABBING:
            this->setCursor(Qt::ClosedHandCursor);
            break;

        case CT_NORTHSOUTHRESIZE:
            this->setCursor(Qt::SizeVerCursor);
            break;

        case CT_EASTWESTRESIZE:
            this->setCursor(Qt::SizeHorCursor);
            break;

        case CT_NORTHEASTRESIZE:
            this->setCursor(Qt::SizeBDiagCursor);
            break;

        case CT_NORTHWESTRESIZE:
            this->setCursor(Qt::SizeFDiagCursor);
            break;

        case CT_MOVE:
            this->setCursor(Qt::SizeAllCursor);
            break;

        case CT_NOTALLOWED:
            this->setCursor(Qt::ForbiddenCursor);
            break;

        case CT_ROWRESIZE:
            this->setCursor(Qt::SplitVCursor);
            break;

        case CT_COLUMNRESIZE:
            this->setCursor(Qt::SplitVCursor);
            break;

        default:
            this->setCursor(Qt::ArrowCursor);
            break;
    }
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
    this->forceActiveFocus();

    CefMouseEvent cefmouseevent;
    cefmouseevent.x = mouseevent->x();
    cefmouseevent.y = mouseevent->y();
    cefmouseevent.modifiers = this->getMouseModifiers(mouseevent);

    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();
    browser->GetHost()->SendMouseClickEvent(cefmouseevent, this->getMouseButtons(mouseevent), false, 1);
}

void QQuickChromiumWebView::mouseMoveEvent(QMouseEvent *mouseevent)
{
    CefMouseEvent cefmouseevent;
    cefmouseevent.x = mouseevent->x();
    cefmouseevent.y = mouseevent->y();
    cefmouseevent.modifiers = this->getMouseModifiers(mouseevent);

    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();
    browser->GetHost()->SendMouseMoveEvent(cefmouseevent, false);
}

void QQuickChromiumWebView::mouseReleaseEvent(QMouseEvent *mouseevent)
{
    CefMouseEvent cefmouseevent;
    cefmouseevent.x = mouseevent->x();
    cefmouseevent.y = mouseevent->y();
    cefmouseevent.modifiers = this->getMouseModifiers(mouseevent);

    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();
    browser->GetHost()->SendMouseClickEvent(cefmouseevent, this->getMouseButtons(mouseevent), true, 1);
}

void QQuickChromiumWebView::wheelEvent(QWheelEvent *wheelevent)
{
    CefMouseEvent cefmouseevent;
    cefmouseevent.x = wheelevent->x();
    cefmouseevent.y = wheelevent->y();
    cefmouseevent.modifiers = this->getMouseModifiers(wheelevent);

    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();

    if(wheelevent->orientation() == Qt::Horizontal)
        browser->GetHost()->SendMouseWheelEvent(cefmouseevent, (wheelevent->delta() / 120.0) * 3 * 20.0, 0);
    else
        browser->GetHost()->SendMouseWheelEvent(cefmouseevent, 0, (wheelevent->delta() / 120.0) * 3 * 20.0);
}

void QQuickChromiumWebView::keyPressEvent(QKeyEvent *keyevent)
{
    CefRefPtr<CefBrowser> browser = this->_handler->GetBrowser();
    CefKeyEvent cefkeyevent;

    cefkeyevent.type = KEYEVENT_RAWKEYDOWN;
    cefkeyevent.modifiers = this->getKeyModifiers(keyevent);
    cefkeyevent.windows_key_code = keyevent->nativeVirtualKey() & 0x00FF;
    cefkeyevent.native_key_code = keyevent->nativeVirtualKey();
    browser->GetHost()->SendKeyEvent(cefkeyevent);

    if(!keyevent->text().isEmpty())
    {
        cefkeyevent.type = KEYEVENT_CHAR;
        cefkeyevent.character = keyevent->text().at(0).unicode();
        browser->GetHost()->SendKeyEvent(cefkeyevent);
    }
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

CefBrowserHost::MouseButtonType QQuickChromiumWebView::getMouseButtons(QMouseEvent *mouseevent)
{
    if (mouseevent->button() == Qt::LeftButton || (mouseevent->buttons() & Qt::LeftButton))
        return MBT_LEFT;
    else if (mouseevent->button() == Qt::RightButton || (mouseevent->buttons() & Qt::RightButton))
        return MBT_RIGHT;
    else if (mouseevent->button() == Qt::MidButton || (mouseevent->buttons() & Qt::MidButton))
        return MBT_MIDDLE;

    return static_cast<CefBrowserHost::MouseButtonType>(0);
}

uint32 QQuickChromiumWebView::getKeyModifiers(QKeyEvent *keyevent)
{
    switch(keyevent->key())
    {
        case Qt::Key_Shift:
            return EVENTFLAG_SHIFT_DOWN;

        case Qt::Key_Alt:
            return EVENTFLAG_ALT_DOWN;

        case Qt::Key_Control:
            return EVENTFLAG_CONTROL_DOWN;

        default:
            break;
    }

    return EVENTFLAG_NONE;
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

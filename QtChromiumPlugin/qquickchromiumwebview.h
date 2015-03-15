#ifndef QQUICKCHROMIUMWEBPAGE_H
#define QQUICKCHROMIUMWEBPAGE_H

#include <QQuickItem>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QDebug>
#include <chromiumapplication.h>
#include <chromiumhandler.h>
#include "loadrequest.h"

class QQuickChromiumWebView : public QQuickItem, public ChromiumHandler::Listener
{
    Q_OBJECT
    Q_DISABLE_COPY(QQuickChromiumWebView)

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QUrl favicon READ favicon NOTIFY faviconChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(bool canGoBack READ canGoBack NOTIFY canGoBackChanged)
    Q_PROPERTY(bool canGoForward READ canGoForward NOTIFY canGoForwardChanged)

    public:
        QQuickChromiumWebView(QQuickItem *webview = 0);
        ~QQuickChromiumWebView();
        bool loading() const;
        bool canGoBack() const;
        bool canGoForward() const;
        QString title() const;
        const QUrl& favicon() const;
        QUrl url() const;
        void setUrl(const QUrl &url);

    public slots:
        void stop();
        void reload();
        void goBack();
        void goForward();

    public: /* ChromiumHandler::Listener Methods */
        virtual void OnAddressChange(const QString&);
        virtual void OnFaviconChange(const QUrl& url);
        virtual void OnTitleChange(const QString& title);
        virtual void SetNavState(bool cangoback, bool cangoforward);
        virtual void OnAfterCreated();
        virtual bool GetViewRect(CefRect &rect);
        virtual void OnPaint(CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList &dirtyrects, const void *buffer, int width, int height);
        virtual void OnCursorChange(CefRenderHandler::CursorType type, const CefCursorInfo &);
        virtual void OnLoadStart(CefRefPtr<CefFrame> frame);
        virtual void OnLoadEnd(CefRefPtr<CefFrame> frame, int httpstatuscode);
        virtual void OnLoadError(CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorcode, const CefString &errortext, const CefString &failedurl);
        virtual void OnMessageEvent(ChromiumMessageEvent* e);

    protected:
        virtual QSGNode* updatePaintNode(QSGNode* oldnode, UpdatePaintNodeData*);
        virtual void focusInEvent(QFocusEvent* focusevent);
        virtual void focusOutEvent(QFocusEvent* focusevent);
        virtual void mousePressEvent(QMouseEvent* mouseevent);
        virtual void mouseMoveEvent(QMouseEvent* mouseevent);
        virtual void mouseReleaseEvent(QMouseEvent* mouseevent);
        virtual void hoverMoveEvent(QHoverEvent *hoverevent);
        virtual void wheelEvent(QWheelEvent *wheelevent);
        virtual void keyPressEvent(QKeyEvent* keyevent);

    private:
        QSGTexture* renewTexture();
        CefBrowserHost::MouseButtonType getMouseButtons(QMouseEvent* mouseevent);
        uint32 getKeyModifiers(QKeyEvent* keyevent);

        template<typename T> uint32 getMouseModifiers(T* event)
        {
            uint mbt = EVENTFLAG_NONE;

            if(event->buttons() & Qt::LeftButton)
                mbt |= EVENTFLAG_LEFT_MOUSE_BUTTON;

            if(event->buttons() & Qt::RightButton)
                mbt |= EVENTFLAG_RIGHT_MOUSE_BUTTON;

            if(event->buttons() & Qt::MiddleButton)
                mbt |= EVENTFLAG_MIDDLE_MOUSE_BUTTON;

            return mbt;
        }

    signals:
        void loadingChanged(LoadRequest* loadRequest);
        void canGoBackChanged();
        void canGoForwardChanged();
        void faviconChanged();
        void urlChanged();
        void titleChanged();

    private slots:
        void createBrowser();
        void onWindowChanged(QQuickWindow* window);
        void onResize();

    private:
        bool _cangoback;
        bool _cangoforward;
        bool _loading;
        QString _title;
        QUrl _favicon;

    private:
        const void* _buffer;
        int _texwidth;
        int _texheight;
        QSGTexture* _texture;
        CefRefPtr<ChromiumHandler> _handler;
};

#endif // QQUICKCHROMIUMWEBPAGE_H

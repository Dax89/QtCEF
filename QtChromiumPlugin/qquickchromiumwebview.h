#ifndef QQUICKCHROMIUMWEBPAGE_H
#define QQUICKCHROMIUMWEBPAGE_H

#include <QQuickItem>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>
#include <QDebug>
#include <chromiumapplication.h>
#include <chromiumhandler.h>

class QQuickChromiumWebView : public QQuickItem, public ChromiumHandler::Listener
{
    Q_OBJECT
    Q_DISABLE_COPY(QQuickChromiumWebView)

    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)

    public:
        QQuickChromiumWebView(QQuickItem *webview = 0);
        ~QQuickChromiumWebView();
        QString url();
        void setUrl(const QString& url);

    public: /* ChromiumHandler::Listener Methods */
        virtual void OnAddressChange(const QString& url);
        virtual void OnTitleChange(const QString& title);
        virtual void SetLoading(bool isloading);
        virtual void SetNavState(bool cangoback, bool cangoforward);
        virtual void OnAfterCreated();
        virtual void OnTakeFocus();
        virtual void OnGotFocus();
        virtual bool GetViewRect(CefRect &rect);
        virtual void OnPaint(CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList &dirtyrects, const void *buffer, int width, int height);
        virtual void OnMessageEvent(ChromiumMessageEvent* e);

    protected:
        virtual QSGNode* updatePaintNode(QSGNode* oldnode, UpdatePaintNodeData*);
        virtual void focusInEvent(QFocusEvent* focusevent);
        virtual void focusOutEvent(QFocusEvent* focusevent);
        virtual void mousePressEvent(QMouseEvent* mouseevent);
        virtual void mouseReleaseEvent(QMouseEvent* mouseevent);
        virtual void keyPressEvent(QKeyEvent* keyevent);

    private:
        QSGTexture* renewTexture();

    signals:
        void urlChanged();

    private slots:
        void createBrowser();
        void onWindowChanged(QQuickWindow* window);
        void onResize();

    private:
        const void* _buffer;
        int _texwidth;
        int _texheight;
        QSGTexture* _texture;
        CefRefPtr<ChromiumHandler> _handler;
};

#endif // QQUICKCHROMIUMWEBPAGE_H

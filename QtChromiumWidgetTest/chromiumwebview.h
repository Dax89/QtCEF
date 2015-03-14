#ifndef CHROMIUMWEBVIEW_H
#define CHROMIUMWEBVIEW_H

#include <QWidget>
#include <QUrl>
#include <QApplication>
#include <QPainter>
#include <QBitmap>
#include <QGLWidget>
#include "chromiumhandler.h"

class ChromiumWebView : public QGLWidget, public ChromiumHandler::Listener
{
    Q_OBJECT

    public:
        explicit ChromiumWebView(QWidget *parent = 0);
        ~ChromiumWebView();

    public:
        void load(const QUrl& url);

    private:
        void createBrowser();
        CefRefPtr<CefBrowser> GetBrowser() const;

    public: /* ChromiumHandler::Listener Methods */
        virtual void OnAddressChange(const QString& url);
        virtual void OnTitleChange(const QString& title);
        virtual void SetLoading(bool isloading);
        virtual void SetNavState(bool cangoback, bool cangoforward);
        virtual void OnAfterCreated();
        virtual void OnGotFocus();
        virtual bool GetViewRect(CefRect &rect);
        virtual void OnPaint(CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList &dirtyrects, const void *buffer, int width, int height);
        virtual void OnMessageEvent(ChromiumMessageEvent* e);

    protected:
        virtual void focusOutEvent(QFocusEvent*);
        virtual void paintEvent(QPaintEvent*);
        virtual void resizeEvent(QResizeEvent*);
        virtual void showEvent(QShowEvent*);
        virtual void closeEvent(QCloseEvent*);

    private:
        QImage _image;
        bool _needsrepaint;
        CefRefPtr<ChromiumHandler> _handler;
};

#endif // CHROMIUMWEBVIEW_H

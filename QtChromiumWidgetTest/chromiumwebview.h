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
        virtual void OnFaviconChange(const QUrl &url);
        virtual void OnTitleChange(const QString& title);
        virtual void SetNavState(bool cangoback, bool cangoforward);
        virtual bool GetViewRect(CefRect &rect);
        virtual void OnPaint(CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList &dirtyrects, const void *buffer, int width, int height);
        virtual void OnCursorChange(CefRenderHandler::CursorType type, const CefCursorInfo &customcursorinfo);
        virtual void OnLoadStart(CefRefPtr<CefFrame> frame);
        virtual void OnLoadEnd(CefRefPtr<CefFrame> frame, int httpstatuscode);
        virtual void OnLoadError(CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorcode, const CefString &errortext, const CefString &failedurl);
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

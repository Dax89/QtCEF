#ifndef WEBPAGERENDERER_H
#define WEBPAGERENDERER_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QDebug>

class WebPageRenderer: public QObject
{
    Q_OBJECT

    public:
        WebPageRenderer();
        ~WebPageRenderer();
        bool isDirty();
        void setBuffer(const void* buffer);
        const void* buffer();
        QOpenGLFramebufferObject* fbo();

    public slots:
        void render();

    private:
        bool _isdirty;
        const void* _buffer;
        QSize _viewportsize;
        QOpenGLFramebufferObject* _fbo;
};

#endif // WEBPAGERENDERER_H

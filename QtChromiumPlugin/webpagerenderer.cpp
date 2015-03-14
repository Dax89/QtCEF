#include "webpagerenderer.h"

WebPageRenderer::WebPageRenderer(): QObject(), _isdirty(true), _buffer(NULL)
{
    //this->initializeOpenGLFunctions();
}

WebPageRenderer::~WebPageRenderer()
{

}

bool WebPageRenderer::isDirty()
{
    return this->_buffer && this->_isdirty;
}

void WebPageRenderer::setBuffer(const void *buffer)
{
    this->_buffer = buffer;
    this->_isdirty = true;
}

const void *WebPageRenderer::buffer()
{
    this->_isdirty = false;
    return this->_buffer;
}

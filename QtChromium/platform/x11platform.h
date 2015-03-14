#ifndef X11PLATFORM_H
#define X11PLATFORM_H

#include "abstractplatform.h"
#include "include/cef_app.h"

class X11Platform : public AbstractPlatform
{
    public:
        X11Platform();
        ~X11Platform();

    public:
        virtual void setFocus(unsigned long winid, bool b);
        virtual void setBounds(unsigned long winid, int x, int y, size_t width, size_t height);
};

#endif // X11PLATFORM_H

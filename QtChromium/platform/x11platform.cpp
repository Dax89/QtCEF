#include "x11platform.h"
#include <X11/Xlib.h>

namespace
{
    void setXWindowBounds(unsigned long winid, int x, int y, size_t width, size_t height)
    {
        XWindowChanges changes = { 0 };
        ::XDisplay* xdisplay = cef_get_xdisplay();

        changes.x = x;
        changes.y = y;
        changes.width = width;
        changes.height = height;

        ::XConfigureWindow(xdisplay, winid, CWX | CWY | CWWidth | CWHeight, &changes);
    }
}

X11Platform::X11Platform()
{

}

X11Platform::~X11Platform()
{

}

void X11Platform::setFocus(unsigned long winid, bool b)
{
    ::XDisplay* xdisplay = cef_get_xdisplay();
    ::XSetInputFocus(xdisplay, (b ? winid : None), RevertToPointerRoot, CurrentTime);
}

void X11Platform::setBounds(unsigned long winid, int x, int y, size_t width, size_t height)
{
    setXWindowBounds(winid, x, y, width, height);
}


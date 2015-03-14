#ifndef ABSTRACTPLATFORM_H
#define ABSTRACTPLATFORM_H

#include <stddef.h>

class AbstractPlatform
{
    public:
        AbstractPlatform();
        ~AbstractPlatform();

    public:
        virtual void setFocus(unsigned long winid, bool b) = 0;
        virtual void setBounds(unsigned long winid, int x, int y, size_t width, size_t height) = 0;
};

#endif // ABSTRACTPLATFORM_H

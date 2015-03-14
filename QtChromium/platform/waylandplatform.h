#ifndef WAYLANDPLATFORM_H
#define WAYLANDPLATFORM_H

#include "abstractplatform.h"

class WaylandPlatform : public AbstractPlatform
{
    public:
        WaylandPlatform();
        ~WaylandPlatform();

    public:
        virtual void setBounds(unsigned long winid, int x, int y, size_t width, size_t height);
};

#endif // WAYLANDPLATFORM_H

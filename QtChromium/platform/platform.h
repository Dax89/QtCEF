#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef X11
    #include "x11platform.h"
    #define Platform X11Platform
#elif WAYLAND
    #include "waylandplatform.h"
    #define Platform WaylandPlatform
#endif


#endif // PLATFORM_H


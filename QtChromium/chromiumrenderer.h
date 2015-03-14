#ifndef CHROMIUMRENDERER_H
#define CHROMIUMRENDERER_H

#include "chromiumapplication.h"

namespace ChromiumRenderer
{
    /* Message sent when the focused node changes. */
    extern const char FocusedNodeChangedMessage[];

    void CreateRendererDelegates(ChromiumApplication::RendererDelegateSet& delegates);
}

#endif // CHROMIUMRENDERER_H

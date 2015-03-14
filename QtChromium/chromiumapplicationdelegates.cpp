#include "chromiumapplication.h"
#include "chromiumrenderer.h"

void ChromiumApplication::CreateBrowserDelegates(ChromiumApplication::BrowserDelegateSet &browserdelegateset)
{

}

void ChromiumApplication::CreateRendererDelegates(ChromiumApplication::RendererDelegateSet &rendererdelegateset)
{
    ChromiumRenderer::CreateRendererDelegates(rendererdelegateset);
}

void ChromiumApplication::RegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar, std::vector<CefString> &cookiable_schemes)
{

}

#include <chromiumapplication.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    CefMainArgs mainargs(argc, argv);
    CefRefPtr<ChromiumApplication> chromiumapp(new ChromiumApplication());
    return CefExecuteProcess(mainargs, chromiumapp.get(), NULL);
}

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtChromium 1.0

Item
{
    property int index

    id: browsertab

    NavigationBar
    {
        id: navigationbar
        anchors { left: parent.left; top: parent.top; right: parent.right }
        favIcon: chromiumwebview.favicon

        onUrlRequested: {
            chromiumwebview.url = req;
        }
    }

    ChromiumWebView
    {
        id: chromiumwebview
        anchors { left: parent.left; top: navigationbar.bottom; right: parent.right; bottom: parent.bottom; topMargin: 2 }

        onUrlChanged: {
            navigationbar.url = url;
        }

        onLoadingChanged: {
            if(loadRequest.loadStatus === LoadRequest.LoadStartedStatus)
                console.log("Load Started");
            else if(loadRequest.loadStatus === LoadRequest.LoadFailedStatus)
                console.log("Load Failed");
            else if(loadRequest.loadStatus === LoadRequest.LoadSucceededStatus)
                console.log("Load Succeeded");
        }

        onTitleChanged: {
            tabview.getTab(index).title = chromiumwebview.title;
        }
    }
}


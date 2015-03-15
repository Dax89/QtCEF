import QtQuick 2.4
import QtQuick.Controls 1.3
import QtChromium 1.0

ApplicationWindow
{
    id: mainwindow
    title: qsTr("QtChromium Test")
    width: 640
    height: 480
    visible: true


    Column
    {
        anchors.fill: parent
        spacing: 5

        Row
        {
            id: row
            width: parent.width
            height: tfurl.height

            Image
            {
                id: favicon
                source: chromiumwebview.favicon
                width: parent.height
                height: parent.height
                fillMode: Image.PreserveAspectFit
            }

            TextField
            {
                id: tfurl
                width: parent.width - btn.width - favicon.width
            }

            Button
            {
                id: btn
                width: 50
                text: "Go"

                onClicked: {
                    if(tfurl.text.indexOf("http://") === -1)
                        tfurl.text = "http://" + tfurl.text;

                    chromiumwebview.url = tfurl.text;
                }
            }
        }

        ChromiumWebView
        {
            id: chromiumwebview
            width: parent.width
            height: parent.height - row.height

            onUrlChanged: {
                tfurl.text = url;
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
                mainwindow.title = chromiumwebview.title;
            }
        }
    }
}

import QtQuick 2.4
import QtQuick.Controls 1.3

Row
{
    property alias url: tfurl.text
    property alias favIcon: favicon.source

    signal urlRequested(string req)

    id: row
    height: tfurl.height

    Image
    {
        id: favicon
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
        height: tfurl.height
        text: "Go"

        onClicked: {
            if(tfurl.text.indexOf("http://") === -1)
                tfurl.text = "http://" + tfurl.text;

            urlRequested(tfurl.text);
        }
    }
}

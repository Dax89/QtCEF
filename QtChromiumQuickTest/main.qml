import QtQuick 2.4
import QtQuick.Controls 1.3

ApplicationWindow
{
    id: mainwindow
    title: qsTr("QtChromium Test")
    width: 640
    height: 480
    visible: true

    TabView
    {
        id: tabview
        anchors.fill: parent
        Component.onCompleted: tabview.addTab("", Qt.createComponent(Qt.resolvedUrl("BrowserTab.qml")));
    }
}

import QtQuick 2.0

Item {
    visible: true
    Component.onCompleted:
    {
        myControl.retranslate()
        console.log("screen2 created")
    }
    QTabBar2 {
        id: idListView
        anchors.fill: parent
        anchors.top: parent.top
        anchors.topMargin: 20
    }
}

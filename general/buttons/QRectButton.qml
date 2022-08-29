import QtQuick 2.0
import "../"

Text{
    id: idRectBtn
    width: 80
    height: 20
    signal btnClicked()
    property color border: "transparent"

    horizontalAlignment: Text.AlignHCenter

    QToolTip {
        mouseID: idBtnArea
        btnLabel: ""
        btnID: idRectBtn
    }

    MouseArea {
        id: idBtnArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            idRectBtn.btnClicked()
        }
    }
    Rectangle{
        anchors.centerIn: parent
        width: parent.width*1.2
        height: width
        radius: width/2
        color: "transparent"
        border.color: parent.border
    }
}


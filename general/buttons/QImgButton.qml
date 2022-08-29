import QtQuick 2.0
import "../"

Image{
    id: idImgBtn
    width: 40
    height: width
    signal btnClicked()
    property string btnLabel
    property color border: "transparent"

    anchors.verticalCenter: parent.verticalCenter
    QToolTip {
        mouseID: idBtnArea
        btnLabel: parent.btnLabel
        btnID: idImgBtn
    }

    MouseArea {
        id: idBtnArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            idImgBtn.btnClicked()
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


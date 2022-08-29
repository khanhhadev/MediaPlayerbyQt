import QtQuick 2.0
import "../libs/Lib.js" as RS
import "./delegates"

Rectangle
{
    id: menuBar
    signal menuClicked()
    signal viewClicked()
    width: parent.width
    height: 20
    color: RS.Color.songback2

    Row{
        QTextBox
        {
            text: qsTr("Menu")
            textRunning: false
            height: 20
            width: 60
            radius: 0
            color: "transparent"
            border.width: 0
            hoverEnabled: false
            onClicked: menuBar.menuClicked()
        }

        QTextBox
        {
            text: qsTr("View")
            textRunning: false
            height: 20
            width: 60
            radius: 0
            color: "transparent"
            border.width: 0
            hoverEnabled: false
            onClicked: menuBar.viewClicked()
        }
    }
}

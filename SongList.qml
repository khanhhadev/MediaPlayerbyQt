import QtQuick 2.0
import "ImageLib.js" as Pic

ListView {
    signal qmlChangeDirectory()
    Component {
        id: fileDelegate
        Rectangle{
            id: idRect
            height: 35
            implicitWidth: idListView.width
            radius: 3
            border.color: focus? "white" : "#2E4D5F"
            opacity: 1
            clip: true
            color: focus? "#2E4D5F" : "transparent"
            Text {
                id: idText
                text: " " + modelData
                fontSizeMode: Text.Fit
                color: parent.focus? "white" : "black"
                elide: Text.ElideRight
                anchors.verticalCenter: parent.verticalCenter
            }
            onFocusChanged: {
                if (!focus) idText.x = parent.x
            }

            //text moving animation
            NumberAnimation{
                properties: "x"
                target: idText
                from: idRect.x
                to: idRect.x - idRect.width
                duration: 4000
                loops: Animation.Infinite
                running: idRect.focus? true: false
            }
            MouseArea {
                id: playArea
                anchors.fill: parent
                onClicked: {
                    var temp = myPlayer.state
                    myData.currentIndex = index
                    myPlayer.state = temp
                }
                onDoubleClicked: {
                    myData.currentIndex = index
                    myPlayer.play()
                }
            }
        }
    }

    delegate: fileDelegate

    Rectangle{
        anchors.fill: parent
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: -7
        radius: 5
        opacity: 0.6
        z: -1
        implicitHeight: parent.height
        color: "white"
        border.color: "white"
    }

    Image
    {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: parent.width/5
        height: width
        source: Pic.add

        MouseArea{
            anchors.fill: parent
            onClicked: {
                mainWindow.qmlChangeDirectory()
            }
        }
    }
}

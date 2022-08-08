import QtQuick 2.0


Rectangle {
    //    id: idSlider
    //    anchors.top: parent.top
    //    anchors.topMargin: 10
    //    anchors.left: songPosition.right
    //    anchors.leftMargin: 10
    //    anchors.right: songDuration.left
    //    anchors.rightMargin: 10
    //    radius: 3
    //    height: 12
    //    clip: true
    //    color: "white"
    id: idSlider
    property real maxValue
    property real currentValue
    property real mheight
    property real mwidth
//    property alias g
    signal mcurrentValueChanged(real value)
    Component.onCompleted: console.log(x, idProgressPoint.x);
    Rectangle {
        id: idProgressRange
        width: idProgressPoint.x - x + idProgressPoint.width / 2
        height: parent.height
        radius: 3
        color: "#877194"
    }

    MouseArea {
        id: progressArea
        anchors.fill: parent
        onClicked: (event) => {
                       mcurrentValueChanged(maxValue * (event.x)/(idSlider.width - idProgressPoint.width))
                       console.log(currentValue, maxValue);
                   }

        Rectangle {
            id: idProgressPoint
            x: (idSlider.width - width) * currentValue / maxValue
            width: idSlider.width/25
            height: parent.height
            z: 1
            radius: 3
            color: "#2E4D5F"
            Drag.active: progressDrag.drag.active
            onXChanged: {
                console.log(idSlider.x,idProgressPoint.x)
                if (progressDrag.drag.active) mcurrentValueChanged(maxValue * idProgressPoint.x/(idSlider.width - idProgressPoint.width))
            }

            states: [State {
                    when: progressDrag.drag.active
                    PropertyChanges{
                        target: idProgressPoint
                        color: "#253E4C"
                        x: progressDrag.x
                    }
                },
                State {
                    when: progressArea.released
                    PropertyChanges{
                        target: idProgressPoint
                        color: "#253E4C"
                        x: progressArea.x
                    }
                }
            ]

            MouseArea {
                id: progressDrag
                anchors.fill: parent
                drag.target: idProgressPoint
                drag.axis: Drag.XAxis
                drag.minimumX: 0
                drag.maximumX: idSlider.width - idProgressPoint.width
            }
        }
    }
}

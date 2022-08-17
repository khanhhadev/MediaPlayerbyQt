import QtQuick 2.0
import "../../libs/ColorLib.js" as Color

//slider design for Progress & Volume display
Rectangle {
    id: idSlider
    property real maxValue
    property real currentValue
    property real mheight
    property real mwidth

    property string dragAreaLabel
    property MouseArea dragAreaID: progressDrag

    signal mcurrentValueChanged(real value)
    signal dragActive(bool active)

    Rectangle {
        id: idProgressRange
        width: idProgressPoint.x - x + idProgressPoint.width / 2
        height: parent.height
        radius: 3
        color: Color.proRange
    }

    MouseArea {
        id: progressArea
        anchors.fill: parent
        onClicked: (event) => {
                       mcurrentValueChanged(maxValue * (event.x)/(idSlider.width - idProgressPoint.width))
                   }

        Rectangle {
            id: idProgressPoint
            x: (idSlider.width - width) * currentValue / maxValue
            width: idSlider.width/22
            height: parent.height*1.2
            z: 1
            radius: 3
            color: Color.proPoint
            Drag.active: progressDrag.drag.active
            onXChanged: {
                if (progressDrag.drag.active) mcurrentValueChanged(maxValue * idProgressPoint.x/(idSlider.width - idProgressPoint.width))
            }
            states: [State {
                    when: progressDrag.drag.active
                    PropertyChanges{
                        target: idProgressPoint
                        color: Color.proPointPressing
                        x: progressDrag.x
                    }
                },
                State {
                    when: progressArea.released
                    PropertyChanges{
                        target: idProgressPoint
                        x: progressArea.x
                    }
                }
            ]

            MouseArea {
                id: progressDrag
                anchors.fill: parent
                hoverEnabled: true
                drag.target: idProgressPoint
                drag.axis: Drag.XAxis
                drag.minimumX: 0
                drag.maximumX: idSlider.width - idProgressPoint.width
            }
        }
    }
}

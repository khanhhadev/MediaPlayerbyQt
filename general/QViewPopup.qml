import QtQuick 2.0
import "../libs/Lib.js" as RS
import "./delegates"

Rectangle
{
    id: idPopUp
    signal sortList(bool Asc)
    border.width: 1
    border.color: "#151A7B"
    visible: false
    enabled: visible

    property var view : [qsTr("Sort by name: Ascending"), qsTr("Sort by name: Descending")]
    Component.onCompleted:
    {
        myControl.retranslate()
    }
    Column
    {
        Repeater{
            model: view.length
            QPopUpItem {
                id: sortOption
                text: view[index]
                width: 160
                onClicked: {
                    sortList(index === 0)
                    idPopUp.visible = false
                }
            }
        }
    }
}

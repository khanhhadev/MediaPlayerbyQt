import QtQuick 2.0
import "../libs/Lib.js" as RS
import "./delegates"

Rectangle
{
    id: idPopUp
    property int currentPage: 1
    signal changeScr(int pageIndex)
    border.width: 1
    border.color: "#151A7B"
    visible: false
    enabled: visible
    property var menu: [
        [qsTr("Libraries"), qsTr("Open Folder"), qsTr("Add Files"), qsTr("Languages"), qsTr("About")],
        [qsTr("Back"), qsTr("Open Folder"), qsTr("Add Files"), qsTr("Languages"), qsTr("About")]
    ];

    Component.onCompleted:
    {
        myControl.retranslate()
    }

    MouseArea{
        id: boxArea
        anchors.fill: cm
        hoverEnabled: true
    }

    Column{
        QPopUpItem {
            id: librarySelect
            text: menu[currentPage - 1][0]
            onClicked: {
                currentPage = currentPage%2 + 1
                changeScr(currentPage)
                idPopUp.visible = false
                console.log(currentPage)
            }
        }

        QPopUpItem {
            id: folderOpen
            text: menu[currentPage - 1][1]
            onClicked: {
                myControl.changeDirectory()
                idPopUp.visible = false
            }
        }

        QPopUpItem {
            id: filesAdd
            text: menu[currentPage - 1][2]
            onClicked: {
                myControl.addFiles()
                idPopUp.visible = false
            }
        }


        QPopUpItem {
            id: languageChange
            text: menu[currentPage - 1][3]
        }

        QPopUpItem {
            id: about
            text: menu[currentPage - 1][4]
            onClicked: {
                idPopUp.visible = false
                var component = Qt.createComponent("qrc:/about.qml")
                var window    = component.createObject(mainWindow)
                window.show()
            }
        }
    }

    Column
    {
        id: cm
        y: languageChange.y
        x: languageChange.x + languageChange.width - 10
        visible: languageChange.hovered || boxArea.containsMouse
        enabled: visible
        Repeater
        {
            id: rpt
            model: RS.Language.length
            QPopUpItem {
                id: lang
                text: RS.Language[index].label
                onClicked: {
                    myControl.setLanguage(RS.Language[index].langID)
                    idPopUp.visible = false
                }
            }
        }
    }
}

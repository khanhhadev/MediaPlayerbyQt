import QtQuick 2.15
import QtQuick.Window 2.12
import "./libs/Lib.js" as RS
import "./screen1"
import "./screen2"
import "./general"

Window {
    id: mainWindow
    width: 900
    height: 640
    visible: true
    title: qsTr("Media Player")
    property int currentPage: 1
    Component.onCompleted:
    {
        myControl.retranslate()
        console.log("main window created")
    }

    Column{
        width: parent.width
        height: parent.height
        QMenuBar{
            id: idMenuBar
            onMenuClicked:
            {
                idMenuPopup.visible = !idMenuPopup.visible
                idViewPopup.visible = false;
            }
            onViewClicked:
            {
                idViewPopup.visible = !idViewPopup.visible
                idMenuPopup.visible = false;
            }
        }

        Loader{
            id: screen
            height: mainWindow.height - idMenuBar.height - idMediaControl.height
            width: mainWindow.width - 20
            source: mainWindow.currentPage === 1? RS.menuLoader.screen1 : RS.menuLoader.screen2

            MouseArea {
                anchors.fill: screen
                onClicked:
                {
                    idViewPopup.visible = false
                    idMenuPopup.visible = false
                }
            }
        }

        //containing media control buttons
        QPlayerControl{
            id: idMediaControl
            anchors{
                left: parent.left
                right: parent.right
            }
        }
    }

    QMenuPopUp {
        id: idMenuPopup
        y : idMenuBar.height
        onChangeScr: (pageIndex) =>{
                         mainWindow.currentPage = pageIndex
                         screen.source = mainWindow.currentPage === 1? RS.menuLoader.screen1 : RS.menuLoader.screen2
                     }
    }

    QViewPopup {
        id: idViewPopup
        y: idMenuBar.height
        x: 60
        onSortList :(asc) =>{
                        myControl.sortList(asc)
                    }
    }
}

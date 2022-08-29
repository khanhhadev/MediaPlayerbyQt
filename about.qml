import QtQuick 2.15
import QtQuick.Window 2.12
import "./libs/Lib.js" as RS

Window {
    id: mainWindow
    width: 300
    height: 250
    visible: true
    title: qsTr("Software Information")
    color: RS.Color.songback2

    property variant swInforHeader: [qsTr("<b>SOFTWARE INFORMATION: </b>\n"),
        "",
        qsTr("Version: ") + "1.0.0" ,
        qsTr("Copyright by: ") + "TUI",
        qsTr("Contact: "),
        qsTr("  By email: ")+ "hatrannguyenkhanh@gmail.com",
        qsTr("  By FB: ")+ "fb.com/trannguyenkhanhha"
    ]
    Component.onCompleted:
    {
        myControl.retranslate()
        console.log("main window created")
    }
    Column{
        anchors.centerIn: parent
        Repeater{
            model: swInforHeader
            Text{
                text:  swInforHeader[index]
                font.bold: (index === 0)? true : false
                color: RS.Color.songtext2
            }
        }
    }
}

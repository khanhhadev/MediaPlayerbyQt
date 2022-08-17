import QtQuick 2.0
import "../../libs/ImageLib.js" as Pic

Row {
    spacing: 5

    Image {
        id: vietnam
        source: Pic.vietnam
        height: 15
        width: 22
        z: parent.z -1
        MouseArea {
            id: vilang
            hoverEnabled: true
            anchors.fill: parent
            onClicked: myControl.setLanguage(1)
        }
        MouseLabel{
            mouseID: vilang
            mouseLabel: "Tiếng Việt"
            imgID: vietnam
        }
    }
    Image {
        id: united
        source: Pic.united
        height: 15
        width: 22
        z: parent.z -1
        MouseArea {
            id: enlang
            hoverEnabled: true
            anchors.fill: parent
            onClicked: myControl.setLanguage(2)
        }
        MouseLabel{
            mouseID: enlang
            mouseLabel: "English"
            imgID: united
        }
    }
    Image {
        id: japan
        source: Pic.japan
        height: 15
        width: 22
        z: parent.z -1
        MouseArea {
            id: jplang
            hoverEnabled: true
            anchors.fill: parent
            onClicked: myControl.setLanguage(3)
        }
        MouseLabel{
            mouseID: jplang
            mouseLabel: "日本語"
            imgID: japan
        }
    }
}

import QtQuick 2.0
import "../../libs/ImageLib.js" as Pic

Row {
    spacing: 5
    Repeater
    {
        model: Pic.Language.length
        Image {
            id: country
            source: Pic.Language[index].source
            height: 15
            width: 22
            z: parent.z -1
            MouseArea {
                id: vilang
                hoverEnabled: true
                anchors.fill: parent
                onClicked: myControl.setLanguage(Pic.Language[index].langID)
            }
            MouseLabel{
                mouseID: vilang
                mouseLabel: Pic.Language[index].label
                imgID: country
            }
        }
    }
}

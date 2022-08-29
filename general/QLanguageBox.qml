import QtQuick 2.0
import "../libs/ImageLib.js" as Pic
import "./buttons"

Row {
    spacing: 5
    Repeater
    {
        model: Pic.Language.length
        QImgButton {
            id: country
            source: Pic.Language[index].source
            height: 15
            width: 22
            z: parent.z -1
            onBtnClicked: myControl.setLanguage(Pic.Language[index].langID)
            btnLabel: Pic.Language[index].label
        }
    }
}

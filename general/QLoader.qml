import QtQuick 2.0



Loader {
    id: listLoader
    sourceComponent: Pic.listMode[idSongList.currentIndex].sourcecomponent;
}

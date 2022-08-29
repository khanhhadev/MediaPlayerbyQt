.pragma library


var Color =
        {
    songback1 : "#151A7B",
    songback2 : "#E5DEE9",

    songborder1 : "#E5DEE9",
    songborder2 : "#151A7B",

    songtext1 : "white",
    songtext2 : "#151A7B",

    border : "#151A7B",

    buttonback1 : "white",
    buttonback2 : "transparent",

    proRange : "#877194",
    proPoint : /*"#2E4D5F"*/ "#151A7B",
    proPointPressing : "#253E4C"
}

var Pic =
        {
    background : "qrc:/image/background.jpg",
    add : "qrc:/image/add.png",
    begin : "qrc:/image/begin.png",
    folder : "qrc:/image/folder.png",
    library : "qrc:/image/library.png",
    music : "qrc:/image/amusic.png",
    mute : "qrc:/image/mute.png",
    volume : "qrc:/image/volume.png",
    next : "qrc:/image/next.png",
    previous : "qrc:/image/previous.png",
    play : "qrc:/image/play.png",
    pause : "qrc:/image/pause.png",
    main : "qrc:/image/main.jpg",
    fastfoward : "qrc:/image/fastfoward.png",
    repeat : "qrc:/image/repeat.png",
    shuffle : "qrc:/image/shuffle.png",
    sort : "qrc:/image/sort.png",
    vietnam : "qrc:/image/vietnam.png",
    japan : "qrc:/image/japan.png",
    united : "qrc:/image/united.png",
    artist : "qrc:/image/artist.png",
    heart : "qrc:/image/heart.png",
    hearted : "qrc:/image/hearted.png"
}


var menuLoader =
        {
    screen1 : "qrc:/screen1/QPlaybackScreen.qml",
    screen2 : "qrc:/screen2/QLibraryScreen.qml",
    languageBox : "qrc:/general/QLanguageBox.qml",
    aboutBox : ""
}

var listMode = [
            {
                name: qsTr("Playlist"),
                src: "qrc:/general/delegates/QSong.qml",
                comsrc: "qrc:/screen1/QSongList.qml",
                comsrc2: "qrc:/screen2/QSongGrid.qml"
            },
            {
                name: qsTr("Artist"),
                src: "qrc:/general/delegates/QArtist.qml",
                comsrc: "qrc:/screen1/QArtistList.qml",
                comsrc2: "qrc:/screen2/QArtistGrid.qml"
            },
            {
                name: qsTr("Album"),
                src: "qrc:/general/delegates/QAlbum.qml",
                comsrc: "qrc:/screen1/QAlbumList.qml",
                comsrc2: "qrc:/screen2/QAlbumGrid.qml"
            },
            {
                name: qsTr("Mylist"),
                src: "qrc:/general/delegates/QSong.qml",
                comsrc: "qrc:/screen1/QSongList.qml",
                comsrc2: "qrc:/screen2/QSongGrid.qml"
            }
        ]

var Language = [
            {
                source: Pic.vietnam,
                langID: "mediaplayer_vi.qm",
                label: "Tiếng Việt"
            },
            {
                source: Pic.united,
                langID: "mediaplayer_en.qm",
                label: "English"
            },

            {
                source: Pic.japan,
                langID: "mediaplayer_jp.qm",
                label: "日本語"
            }

        ]



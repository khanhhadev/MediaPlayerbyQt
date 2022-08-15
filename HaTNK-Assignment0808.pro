QT += \
    quick \
    multimedia \
    multimediawidgets \
    core \
    widgets \

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        browserdialog.cpp \
        main.cpp \
        mediacontrol.cpp \
        mediadatalist.cpp \
        player.cpp

RESOURCES += qml.qrc

TRANSLATIONS = mediaplayer_en.ts mediaplayer_jp.ts mediaplayer_vi.ts
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH += \
        SongList.qml \
        PlayerControl.qml \
        ProgressBar.qml \
        MusicalArea.qml \
        MSlider.qml \
        main.qml

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    browserdialog.h \
    mediacontrol.h \
    mediadatalist.h \
    player.h

DISTFILES += \
    HaTNK-Assignment0808_en.qm \
    HaTNK-Assignment0808_jp.qm \
    HaTNK-Assignment0808_vi.qm

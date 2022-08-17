QT += \
    quick \
    multimedia \
    core \
    widgets \
    xml

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Control/Support/browserdialog.cpp \
        Control/Support/datastorage.cpp \
    Control/Support/languageset.cpp \
        Control/mediacontrol.cpp \
        Model/mediadatalist.cpp \
        Model/player.cpp \
        main.cpp \

RESOURCES += qml.qrc

TRANSLATIONS = mediaplayer_en.ts mediaplayer_jp.ts mediaplayer_vi.ts
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH += \
        subparts/SongList.qml \
        subparts/PlayerControl.qml \
        subparts/MusicalArea.qml \
        subparts/subcomponents/MSlider.qml \
        subparts/subcomponents/LanguageBox.qml \
        main.qml

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Control/Support/browserdialog.h \
    Control/Support/datastorage.h \
    Control/Support/languageset.h \
    Control/mediacontrol.h \
    Model/mediadatalist.h \
    Model/player.h \

DISTFILES += \
    HaTNK-Assignment0808_en.qm \
    HaTNK-Assignment0808_jp.qm \
    HaTNK-Assignment0808_vi.qm

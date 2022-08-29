QT += \
    quick \
    multimedia \
    core \
    widgets \

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        controls/Support/browserdialog.cpp \
        controls/Support/languageset.cpp \
        controls/mediacontrol.cpp \
        models/player.cpp \
        models/playlist.cpp \
        models/subelements/albumelement.cpp \
        models/subelements/artistelement.cpp \
        models/subelements/imageitem.cpp \
        models/subelements/songelement.cpp \
        models/subelements/songloader.cpp \
        main.cpp \

RESOURCES += qml.qrc

TRANSLATIONS += languages/mediaplayer_en.ts \
                languages/mediaplayer_jp.ts \
                languages/mediaplayer_vi.ts
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    controls/Support/browserdialog.h \
    controls/Support/languageset.h \
    controls/Support/setting.h \
    controls/mediacontrol.h \
    models/player.h \
    models/playlist.h \
    models/subelements/imageitem.h \
    models/subelements/songelement.h \
    models/subelements/songloader.h \
    models/subelements/albumelement.h \
    models/subelements/artistelement.h \

DISTFILES += \
    languages/mediaplayer_en.qm \
    languages/mediaplayer_jp.qm \
    languages/mediaplayer_vi.qm

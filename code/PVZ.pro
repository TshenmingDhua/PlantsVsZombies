QT       += core gui multimedia multimediawidgets
QT  +=  multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cooldowndark.cpp \
    gamemap.cpp \
    gamemedia.cpp \
    main.cpp \
    peas.cpp \
    plants.cpp \
    plantscard.cpp \
    plantthread.cpp \
    setplants.cpp \
    shootbox.cpp \
    smallcar.cpp \
    spade.cpp \
    sunshine.cpp \
    zombies.cpp

HEADERS += \
    cooldowndark.h \
    gamemap.h \
    gamemedia.h \
    peas.h \
    plants.h \
    plantscard.h \
    plantthread.h \
    setplants.h \
    shootbox.h \
    smallcar.h \
    spade.h \
    sunshine.h \
    zombies.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=

RESOURCES += \
    res.qrc

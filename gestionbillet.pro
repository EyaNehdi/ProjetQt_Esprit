QT       += core gui printsupport
QT       += sql
QT +=serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = ProjetA2
CONFIG += c++11


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
    arduino.cpp \
    billet.cpp \
    connection.cpp \
    dialog_stats.cpp \
    exportexcelobject.cpp \
    gestion_billet.cpp \
    main.cpp \
    qcustomplot.cpp \
    qrcode.cpp

HEADERS += \
    arduino.h \
    billet.h \
    connection.h \
    dialog_stats.h \
    exportexcelobject.h \
    gestion_billet.h \
    qcustomplot.h \
    qrcode.h

FORMS += \
    dialog_stats.ui \
    gestion_billet.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    gestionbillet.qrc

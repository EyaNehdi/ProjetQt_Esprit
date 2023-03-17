QT       += core gui sql serialport charts
QT       += network
QT       += printsupport
QT       += charts
QT       +=multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    dialog_mailing.cpp \
    dialog_stats.cpp \
    etudiant.cpp \
    exportexcelobject.cpp \
    gestion_billet.cpp \
    gestion_vol.cpp \
    gestion_voyageur.cpp \
    main.cpp \
    mainwindow.cpp \
    popup.cpp \
    qcustomplot.cpp \
    qrcode.cpp \
    smtp.cpp \
    statistiques.cpp \
    vol.cpp

HEADERS += \
    ../../../../../Atelier_Connexion/Atelier_ConnexionOracle/popup.h \
    ../../Bureau/2A30-Gestion-des-billets/exportexcelobject.h \
    arduino.h \
    billet.h \
    connection.h \
    dialog_mailing.h \
    dialog_stats.h \
    etudiant.h \
    exportexcelobject.h \
    gestion_billet.h \
    gestion_vol.h \
    gestion_voyageur.h \
    mainwindow.h \
    popup.h \
    qcustomplot.h \
    qrcode.h \
    smtp.h \
    statistiques.h \
    vol.h

FORMS += \
      dialog_mailing.ui \
    dialog_stats.ui \
    gestion_billet.ui \
    gestion_vol.ui \
    gestion_voyageur.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

DISTFILES += \
    image/240004.jpg \
    image/OIP.jfif \
    image/avionpetit.jpg \
    image/lalala.jpg \
    image/smart.png

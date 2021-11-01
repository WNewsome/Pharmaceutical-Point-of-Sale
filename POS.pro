QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addgrug.cpp \
    changedrugwindow.cpp \
    checkout.cpp \
    datastorage.cpp \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    managementscreen.cpp \
    settingsscreen.cpp \
    patientscreen.cpp


HEADERS += \
    addgrug.h \
    changedrugwindow.h \
    checkout.h \
    datastorage.h \
    dialog.h \
    mainwindow.h \
    managementscreen.h \
    settingsscreen.h \
    patientscreen.h

FORMS += \
    addgrug.ui \
    changedrugwindow.ui \
    checkout.ui \
    dialog.ui \
    mainwindow.ui \
    managementscreen.ui \
    settingsscreen.ui \
    patientscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

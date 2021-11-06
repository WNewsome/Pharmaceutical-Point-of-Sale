QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adddrug.cpp \
    addgrug.cpp \
    changedrugwindow.cpp \
    checkout.cpp \
    datastorage.cpp \
    dialog.cpp \
    editdrug.cpp \
    main.cpp \
    mainwindow.cpp \
    managementscreen.cpp \
    settingsscreen.cpp \
    patientscreen.cpp


HEADERS += \
    adddrug.h \
    addgrug.h \
    changedrugwindow.h \
    checkout.h \
    datastorage.h \
    dialog.h \
    editdrug.h \
    mainwindow.h \
    managementscreen.h \
    settingsscreen.h \
    patientscreen.h

FORMS += \
    adddrug.ui \
    addgrug.ui \
    changedrugwindow.ui \
    checkout.ui \
    dialog.ui \
    editdrug.ui \
    mainwindow.ui \
    managementscreen.ui \
    settingsscreen.ui \
    patientscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

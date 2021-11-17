QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += charts

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addgrug.cpp \
    checkout.cpp \
    datastorage.cpp \
    dialog.cpp \
    doubleclicklist.cpp \
    main.cpp \
    mainwindow.cpp \
    managementscreen.cpp \
    newprescription.cpp \
    reports.cpp \
    salescreen.cpp \
    settingsscreen.cpp \
    patientscreen.cpp


HEADERS += \
    addgrug.h \
    checkout.h \
    datastorage.h \
    dialog.h \
    doubleclicklist.h \
    mainwindow.h \
    managementscreen.h \
    newprescription.h \
    reports.h \
    salescreen.h \
    settingsscreen.h \
    patientscreen.h

FORMS += \
    addgrug.ui \
    checkout.ui \
    dialog.ui \
    mainwindow.ui \
    managementscreen.ui \
    newprescription.ui \
    reports.ui \
    salescreen.ui \
    settingsscreen.ui \
    patientscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

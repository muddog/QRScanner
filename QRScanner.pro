#-------------------------------------------------
#
# Project created by QtCreator 2017-02-21T10:56:04
#
#-------------------------------------------------

QT       += core gui

include(QZXing/QZXing.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRScanner
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEBUG {
    DEFINES += DEBUG
}

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


DESKTOP {
    DEFINES += LINUX_HOST
    INCLUDEPATH += /usr/lib/x86_64-linux-gnu/glib-2.0/include/
    INCLUDEPATH += /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include/
}

IMX6UL {
    DEFINES += __ARM_PCS_VFP QT_NO_OPENGL
    INCLUDEPATH += $$[QT_SYSROOT]/usr/include/c++/5.3.0/
    INCLUDEPATH += $$[QT_SYSROOT]/usr/include/c++/5.3.0/arm-poky-linux-gnueabi
}

INCLUDEPATH += $$[QT_SYSROOT]/usr/include/gstreamer-1.0/
INCLUDEPATH += $$[QT_SYSROOT]/usr/lib/glib-2.0/include/
INCLUDEPATH += $$[QT_SYSROOT]/usr/include/glib-2.0/
INCLUDEPATH += $$[QT_SYSROOT]/usr/include/
INCLUDEPATH += $$[QT_SYSROOT]/usr/lib/gstreamer-1.0/include/
LIBS += -L$$[QT_SYSROOT]/lib/ -lpthread -L$$[QT_SYSROOT]/usr/lib/ \
        -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lgstapp-1.0

!DESKTOP {
    target.path = /usr/bin/
    INSTALLS += target
}

SOURCES += main.cpp\
        mainwindow.cpp \
    scannerqwidgetsink.cpp \
    viewfinderwidget.cpp \
    decoderthread.cpp

HEADERS  += mainwindow.h \
    scannerqwidgetsink.h \
    viewfinderwidget.h \
    decoderthread.h

FORMS    += mainwindow.ui

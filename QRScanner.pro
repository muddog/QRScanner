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
    INCLUDEPATH += /usr/include/glib-2.0 \
                   /usr/lib/x86_64-linux-gnu/glib-2.0/include \
                   /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include

    LIBS +=  -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lgstvideo-1.0 -lgstapp-1.0
    DEFINES += LINUX_HOST
}

IMX6UL {
    INCLUDEPATH += /opt/fsl-imx-wayland/4.1.15-2.0.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/include/c++/5.3.0/
    INCLUDEPATH += /opt/fsl-imx-wayland/4.1.15-2.0.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/include/c++/5.3.0/arm-poky-linux-gnueabi/
    INCLUDEPATH += /opt/fsl-imx-wayland/4.1.15-2.0.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/include/
    INCLUDEPATH += /opt/fsl-imx-wayland/4.1.15-2.0.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/include/gstreamer-1.0/
    INCLUDEPATH += /opt/fsl-imx-wayland/4.1.15-2.0.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/lib/glib-2.0/include/
    INCLUDEPATH += /opt/fsl-imx-wayland/4.1.15-2.0.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/include/glib-2.0/
    INCLUDEPATH += /opt/fsl-imx-wayland/4.1.15-2.0.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/lib/gstreamer-1.0/include/
    DEFINES += __ARM_PCS_VFP QT_NO_OPENGL

    LIBS += -L/opt/fsl-imx-wayland/4.1.15-2.0.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/lib/ -lpthread \
            -L/opt/fsl-imx-wayland/4.1.15-2.0.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/lib/ \
            -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lgstapp-1.0

    target.path = /home/root/
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

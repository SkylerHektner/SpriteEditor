#-------------------------------------------------
#
# Project created by QtCreator 2017-10-29T14:00:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpriteStudioDeluxe
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(QtGifImage-master\src\gifimage\qtgifimage.pri)

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    project.cpp \
    frame.cpp \
    canvas.cpp \
    previewobject.cpp \
    tools.cpp

HEADERS += \
        mainwindow.h \
    project.h \
    frame.h \
    frame.h \
    canvas.h \
    previewobject.h \
    tools.h

FORMS += \
        mainwindow.ui

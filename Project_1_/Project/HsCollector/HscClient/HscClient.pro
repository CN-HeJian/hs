#-------------------------------------------------
#
# Project created by QtCreator 2017-03-28T14:29:31
#
#-------------------------------------------------

QT       -= core gui

TARGET = HscClient
TEMPLATE = lib

CONFIG -= qt
CONFIG += c++11

DEFINES += HSCCLIENT_LIBRARY HSC_DEVICE=AI10_DI8_AO0_DO2

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    HscClient.cpp \
    HscMsgIn.cpp

INCLUDEPATH = \
    $$PWD/.

HEADERS +=\
    HscClientHeader.h \
    HscClient.h \
    HscDevice.h \
    HscMsgIOD.h \
    HscMsgIOA.h \
    HscMsgIn.h

#target.path += $$OUT_PWD/../bin
#INSTALLS += target

CONFIG(debug,debug|release){
    DESTDIR = $$OUT_PWD/../../debug
}else{
    DESTDIR = $$OUT_PWD/../../release
}

LIBS += -L$$DESTDIR -lmosquittopp

INCLUDEPATH += $$PWD/../thirdparty/libmosquitto

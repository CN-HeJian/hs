# Created by and for Qt Creator. This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

# 配置工程为qt无关的动态库

QT       -= core gui
CONFIG  -= qt
CONFIG += c++11 shared

TARGET = mosquittopp
TEMPLATE = lib

# only export mosquittopp
#CONFIG(shared, shared|static) : DEFINES += libmosquitto_EXPORTS
CONFIG(shared, shared|static) : DEFINES += mosquittopp_EXPORTS
DEFINES += \
    WITH_THREADING \
    WITH_PERSISTENCE \
    WITH_MEMORY_TRACKING \
    WITH_SYS_TREE \
    WITH_UUID \
    WITH_EC \
    WITH_SOCKS
#    WITH_WEBSOCKETS \
#    WITH_TLS WITH_TLS_PSK \
#    WITH_SRV \

# win32: LIBS += "$$PWD/WS2_32.Lib"

win32: LIBS += -lWS2_32

#LIBS += -lpthread

INCLUDEPATH = \
    $$PWD/.

HEADERS = \
   $$PWD/mosquittopp.h \
   $$PWD/mosquitto.h \
   $$PWD/dummypthread.h \
   $$PWD/logging_mosq.h \
   $$PWD/memory_mosq.h \
   $$PWD/messages_mosq.h \
   $$PWD/mosquitto_internal.h \
   $$PWD/mqtt3_protocol.h \
   $$PWD/net_mosq.h \
   $$PWD/read_handle.h \
   $$PWD/send_mosq.h \
   $$PWD/socks_mosq.h \
   $$PWD/time_mosq.h \
   $$PWD/tls_mosq.h \
   $$PWD/util_mosq.h \
   $$PWD/will_mosq.h \
   $$PWD/config.h

SOURCES = \
   $$PWD/mosquittopp.cpp \
   $$PWD/logging_mosq.c \
   $$PWD/memory_mosq.c \
   $$PWD/messages_mosq.c \
   $$PWD/mosquitto.c \
   $$PWD/net_mosq.c \
   $$PWD/read_handle.c \
   $$PWD/read_handle_client.c \
   $$PWD/read_handle_shared.c \
   $$PWD/send_client_mosq.c \
   $$PWD/send_mosq.c \
   $$PWD/socks_mosq.c \
   $$PWD/srv_mosq.c \
   $$PWD/thread_mosq.c \
   $$PWD/time_mosq.c \
   $$PWD/tls_mosq.c \
   $$PWD/util_mosq.c \
   $$PWD/will_mosq.c

#target.path += $$OUT_PWD/../../bin
#INSTALLS += target

CONFIG(debug,debug|release){
    DESTDIR = $$OUT_PWD/../../../debug
}else{
    DESTDIR = $$OUT_PWD/../../../release
}

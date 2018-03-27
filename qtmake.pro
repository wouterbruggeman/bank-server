TEMPLATE = app
TARGET = server

VPATH += ./src/

QT = core sql network

HEADERS += \
	tcpsocket.h
SOURCES += main.cpp \
	tcpsocket.cpp

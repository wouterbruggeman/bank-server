CONFIG += debug

CONFIG(debug, debug|release) {
	message( "~debug~" )
	DEFINES += DEBUG
}
CONFIG(release, debug|release) {
	message( "~release~" )
}

TEMPLATE = app
TARGET = server
VPATH += ./src

QT = core sql network

HEADERS += \
	config.h \
	db.h \
	iban.h \
	log.h \
	packethandler.h \
	tcpserver.h \
	tcpsocket.h \
	transaction.h \
	transactionhandler.h
SOURCES += main.cpp \
	config.cpp \
	db.cpp \
	iban.cpp \
	log.cpp \
	packethandler.cpp \
	tcpserver.cpp \
	tcpsocket.cpp \
	transaction.cpp \
	transactionhandler.cpp

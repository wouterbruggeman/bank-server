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
VPATH += ./src/
QT = core sql network

HEADERS += \
	db.h \
	iban.h \
	log.h \
	tcpserver.h \
	tcpsocket.h \
	transaction.h \
	config.h
SOURCES += \
	main.cpp \
	db.cpp \
	iban.cpp \
	log.cpp \
	tcpserver.cpp \
	tcpsocket.cpp \
	transaction.cpp \
	config.cpp

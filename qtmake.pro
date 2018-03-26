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

HEADERS
SOURCES += main.cpp

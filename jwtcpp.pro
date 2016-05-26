QT       -= core gui

TARGET = jwtcpp
TEMPLATE = lib

DEFINES += JWTCPP_LIBRARY

SOURCES = sources/jwt.cpp \
	sources/base64.cpp \
	
	sources/algo/hmac.cpp

HEADERS = sources/jwt.h \
	sources/base64.h \
	sources/exception.h \
	sources/algo/algo.h \
	sources/algo/hmac.h \
	vendor/json/src/json.hpp

INCLUDEPATH += vendor/json/src

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG += c++11 -Wall -O0 -Wno-unused-parameter staticlib

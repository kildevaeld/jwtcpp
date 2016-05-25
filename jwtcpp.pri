QT       -= core gui

TARGET = jwtcpp
TEMPLATE = lib

DEFINES += JWTCPP_LIBRARY

CONFIG += c++11 -Wall -O0 -Wno-unused-parameter staticlib

unix {
    target.path = /usr/lib
    INSTALLS += target
}


SOURCES = $$PWD/sources/jwt.cpp \
	$$PWD/sources/base64.cpp \
	$$PWD/sources/algo/algo.cpp
	$$PWD/sources/algo/hmac.cpp

HEADERS = $$PWD/sources/jwt.h \
	$$PWD/sources/base64.h \
	$$PWD/sources/exception.h \
	$$PWD/sources/algo/algo.h \
	$$PWD/sources/algo/hmac.h \
	$$PWD/vendor/json/src/json.hpp

INCLUDEPATH += $$PWD




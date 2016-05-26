QT       -= core gui

TARGET = jwtcpp
TEMPLATE = lib

DEFINES += JWTCPP_LIBRARY

CONFIG += link_pkgconfig c++11 -Wall -O0 -Wno-unused-parameter staticlib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QT_CONFIG -= no-pkg-config

INCLUDEPATH += /usr/local/include


PKGCONFIG += openssl



SOURCES = $$PWD/sources/jwt.cpp \
	$$PWD/sources/base64.cpp \
	$$PWD/sources/algo/hmac.cpp

HEADERS = $$PWD/sources/jwt.h \
	$$PWD/sources/base64.h \
	$$PWD/sources/exception.h \
	$$PWD/sources/algo/algo.h \
	$$PWD/sources/algo/hmac.h \
	$$PWD/vendor/json/src/json.hpp

INCLUDEPATH += $$PWD



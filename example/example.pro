TEMPLATE = app
CONFIG += console c++11 -Wno-unused-parameter static

TARGET = jwt
include(../jwtcpp.pri)

SOURCES += main.cpp

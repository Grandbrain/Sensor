QT       += core gui widgets network

QMAKE_CXXFLAGS += -mno-ms-bitfields

CONFIG += c++11

TARGET = Sensor
TEMPLATE = app


SOURCES += ../Source/main.cpp \
    ../Source/window.cpp \
    ../Source/sensor.cpp

HEADERS  += \
    ../Source/sensor.h \
    ../Source/window.h
FORMS    += ../Source/window.ui

RESOURCES += \
    ../Source/resources.qrc

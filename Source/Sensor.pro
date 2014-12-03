QT       += core gui widgets network

QMAKE_CXXFLAGS += -mno-ms-bitfields
CONFIG += c++11
TARGET = Sensor
TEMPLATE = app

LIBS += -lws2_32

SOURCES 	+= main.cpp window.cpp sensor.cpp about.cpp \
    search.cpp
HEADERS  	+= sensor.h window.h about.h \
    search.h
FORMS    	+= window.ui about.ui \
    search.ui
RESOURCES 	+= resources.qrc

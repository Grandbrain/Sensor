QT              += core gui widgets network

TARGET          = Sensor
TEMPLATE        = app
CONFIG          += c++11;

SOURCES         += main.cpp window.cpp sensor.cpp search.cpp about.cpp
HEADERS  	+= sensor.h window.h search.h about.h
FORMS    	+= window.ui search.ui about.ui
RESOURCES       += resources.qrc
RC_ICONS        = icon.ico

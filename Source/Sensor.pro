QT              += core gui widgets network

TARGET          = Sensor
TEMPLATE        = app
CONFIG          += c++11;

SOURCES         += main.cpp window.cpp sensor.cpp about.cpp splash.cpp
HEADERS  	+= sensor.h window.h about.h splash.h
FORMS    	+= window.ui about.ui splash.ui
RESOURCES       += resources.qrc
RC_FILE         = resources.rc

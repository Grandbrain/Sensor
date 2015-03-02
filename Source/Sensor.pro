QT              += core gui widgets network webenginewidgets

TARGET          = Sensor
TEMPLATE        = app
CONFIG          += c++11;

SOURCES         += main.cpp window.cpp sensor.cpp search.cpp about.cpp splash.cpp
HEADERS  	+= sensor.h window.h search.h about.h splash.h
FORMS    	+= window.ui search.ui about.ui splash.ui
RESOURCES       += resources.qrc
RC_ICONS        = icon.ico

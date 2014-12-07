QT              += core gui widgets network

TARGET          = Sensor
TEMPLATE        = app

SOURCES         += main.cpp window.cpp sensor.cpp about.cpp search.cpp
HEADERS  	+= sensor.h window.h about.h search.h
FORMS    	+= window.ui about.ui search.ui

RESOURCES += \
    resources.qrc

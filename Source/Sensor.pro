QT              += core gui widgets network

TARGET          = Sensor
TEMPLATE        = app
CONFIG          += c++11

SOURCES         += main.cpp window.cpp about.cpp splash.cpp sensor.cpp
HEADERS  	+= window.h about.h splash.h sensor.h
FORMS    	+= window.ui about.ui splash.ui
RESOURCES       += resources.qrc
RC_FILE         = resources.rc
QMAKE_CXXFLAGS  += -std=c++11

win32
{
    #CONFIG += embed_manifest_exe
    #QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:"level='requireAdministrator'"
}

#-------------------------------------------------
#
# Project created by QtCreator 2015-03-06T22:28:07
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = ChromiumProcess
CONFIG   += console
CONFIG   -= app_bundle

LIBS += -L$$OUT_PWD/../QtChromium -lQtChromium -L$$PWD/../ -lcef -lcef_dll_wrapper
INCLUDEPATH += $$PWD/../CEF $$PWD/../QtChromium

TEMPLATE = app
SOURCES += main.cpp

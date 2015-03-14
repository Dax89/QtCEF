#-------------------------------------------------
#
# Project created by QtCreator 2015-03-07T13:00:33
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtChromiumWidgetTest
TEMPLATE = app

INCLUDEPATH += $$PWD/../CEF $$PWD/../QtChromium
LIBS += -L$$OUT_PWD/../QtChromium -lQtChromium -lX11 -L$$PWD/../ -lcef -lcef_dll_wrapper

SOURCES += main.cpp\
        mainwindow.cpp \
    chromiumwebview.cpp

HEADERS  += mainwindow.h \
    chromiumwebview.h

FORMS    += mainwindow.ui

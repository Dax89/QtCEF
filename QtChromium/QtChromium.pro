#-------------------------------------------------
#
# Project created by QtCreator 2015-03-06T22:17:54
#
#-------------------------------------------------

QT       -= gui

TARGET = QtChromium
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += $$PWD/../CEF
LIBS += -L$$PWD/../ -lcef -lcef_dll_wrapper

SOURCES += \
    chromiumhandler.cpp \
    chromiumhandlerqt.cpp \
    chromiummessageevent.cpp \
    chromiumapplication.cpp \
    chromiumapplicationdelegates.cpp \
    chromiumrenderer.cpp \
    chromiumcontext.cpp \
    platform/abstractplatform.cpp \
    platform/x11platform.cpp \
    platform/waylandplatform.cpp \
    platform/platform.cpp

HEADERS += \
    chromiumhandler.h \
    chromiummessageevent.h \
    chromiumapplication.h \
    chromiumrenderer.h \
    chromiumcontext.h \
    platform/abstractplatform.h \
    platform/x11platform.h \
    platform/platform.h \
    platform/waylandplatform.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

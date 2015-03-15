TEMPLATE = lib
TARGET = QtChromiumPlugin
QT += qml quick # quick-private
CONFIG += qt plugin

INCLUDEPATH += $$PWD/../CEF $$PWD/../QtChromium
LIBS += -L$$OUT_PWD/../QtChromium -lQtChromium -L$$PWD/../ -lcef -lcef_dll_wrapper

TARGET = $$qtLibraryTarget($$TARGET)
uri = QtChromium

# Input
SOURCES += \
    qtchromiumplugin_plugin.cpp \
    qquickchromiumwebview.cpp

HEADERS += \
    qtchromiumplugin_plugin.h \
    qquickchromiumwebview.h

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}


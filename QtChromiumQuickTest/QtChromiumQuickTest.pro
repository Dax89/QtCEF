TEMPLATE = app

QT += qml quick widgets

INCLUDEPATH += $$PWD/../CEF $$PWD/../QtChromium
LIBS += -L$$OUT_PWD/../QtChromium -lQtChromium -L$$PWD/../ -lcef -lcef_dll_wrapper

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $OUT_PWD/../QtChromiumPlugin

# Default rules for deployment.
include(deployment.pri)

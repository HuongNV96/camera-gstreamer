TEMPLATE = app
TARGET = camera-gstreamer
HEADERS += Player.h
SOURCES += Player.cpp main.cpp

RESOURCES += app.qrc

INCLUDEPATH += $$PWD/../qt-gstreamer/include/Qt5GStreamer
LIBS += -L$$PWD/../qt-gstreamer/include/Qt5GStreamer/lib/ -lQt5GStreamerQuick-1.0 -lQt5GStreamer-1.0 -lQt5GLib-2.0 -lQt5GStreamerUi-1.0 -lQt5GStreamerUtils-1.0

QT += quick core gui

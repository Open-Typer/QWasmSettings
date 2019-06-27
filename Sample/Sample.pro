TEMPLATE = app

QT += quick quickcontrols2

TARGET = sample

include(../qwasmsettings.pri)

SOURCES += \
	main.cpp

RESOURCES += qml.qrc

wasm: QMAKE_LFLAGS_DEBUG += --emrun

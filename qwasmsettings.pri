wasm {
	HEADERS += $$PWD/qwasmsettings.h

	SOURCES += $$PWD/qwasmsettings.cpp 

	INCLUDEPATH += $$PWD

	QDEP_PACKAGE_EXPORTS += Q_WASM_SETTINGS_EXPORT
	!qdep_build: DEFINES += "Q_WASM_SETTINGS_EXPORT="
}

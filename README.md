# QWasmSettings
A QSettings format for Qt for WebAssembly that uses the local storage API to store settings

## Features
- Uses the [Local Storage](https://www.w3schools.com/html/html5_webstorage.asp) to store application data
- A custom QSettings::Format can be registered to enable this
- Works just like any other QSettings format

## Installation
The package is provided via qdep, as `Skycoder42/QWasmSettings`. To use it simply:

1. Install and enable qdep (See [qdep - Installing](https://github.com/Skycoder42/qdep#installation))
2. Add the following to your pro file:
```qmake
QDEP_DEPENDS += Skycoder42/QWasmSettings
!load(qdep):error("Failed to load qdep feature! Run 'qdep prfgen --qmake $$QMAKE_QMAKE' to create it.")
```

## Example
The following code should be used to create wasm settings. After the registration, it can be used just like any other QSettings. However, you should always only create default constructed QSettings:

```cpp
#ifdef Q_OS_WASM
#include <qwasmsettings.h>
#endif

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	// set name and organization to correctly create the settings
	QCoreApplication::setApplicationName(QStringLiteral("..."));
	QCoreApplication::setOrganizationName(QStringLiteral("..."));

#ifdef Q_OS_WASM
	QWasmSettings::registerFormat(true); // register the format and make it the default format
#endif

	QSettings settings; // or auto settings = new QSettings{&app};
	// use as usual

	// ...

	return app.exec();
}
```

## Usage hints
There are a few limitations with this implementation:

1. There is only *one* local storage. Using different names, organizations or paths makes no difference, they will all use the same storage.
2. Using them is still possible, but requires you to call `QWasmSettings::prepareSettingsFile` on the settings or their path, as the format needs to explicitly register each path for it to work correctly.
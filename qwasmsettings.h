#ifndef QWASMSETTINGS_H
#define QWASMSETTINGS_H

#include <QSettings>

namespace QWasmSettings
{
	
Q_WASM_SETTINGS_EXPORT QSettings::Format registerFormat(bool makeDefault = true);
Q_WASM_SETTINGS_EXPORT void prepareSettingsFile(const QString &path);
Q_WASM_SETTINGS_EXPORT void prepareSettingsFile(QSettings *settings);

};

#endif // QWASMSETTINGS_H

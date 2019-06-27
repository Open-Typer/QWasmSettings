#include "qwasmsettings.h"
#include <QDir>
#include <QUuid>
#include <QDebug>

#include <emscripten/val.h>
using namespace emscripten;

namespace {

QSettings::Format wasmFormat = QSettings::InvalidFormat;

bool readWasmSettings(QIODevice &device, QSettings::SettingsMap &map);
bool writeWasmSettings(QIODevice &device, const QSettings::SettingsMap &map);

}

QSettings::Format QWasmSettings::registerFormat(bool makeDefault)
{
	if (wasmFormat == QSettings::InvalidFormat) {
		wasmFormat = QSettings::registerFormat(QStringLiteral("wasmconf"),
											   readWasmSettings,
											   writeWasmSettings,
											   Qt::CaseSensitive);
		QSettings::setPath(wasmFormat, QSettings::UserScope, QDir::tempPath());
		QSettings::setPath(wasmFormat, QSettings::SystemScope, QDir::tempPath());
		if (makeDefault) {
			QSettings::setDefaultFormat(wasmFormat);
			QSettings mPathOrigin;
			prepareSettingsFile(&mPathOrigin);
		}
	}

	return wasmFormat;
}

void QWasmSettings::prepareSettingsFile(const QString &path)
{
	QFileInfo{path}.dir().mkpath(QStringLiteral("."));
	QFile sFile{path};
	if (!sFile.open(QIODevice::WriteOnly)) {
		qWarning() << "QWasmSettings: Failed to prepare path"
				   << path << "with error:" << qUtf8Printable(sFile.errorString());
		return;
	}

	sFile.write(QUuid::createUuid().toByteArray());
	sFile.close();
}

void QWasmSettings::prepareSettingsFile(QSettings *settings)
{
	Q_ASSERT(settings->format() == wasmFormat);
	prepareSettingsFile(settings->fileName());
	settings->sync();
}

namespace {

bool readWasmSettings(QIODevice &device, QSettings::SettingsMap &map)
{
	Q_UNUSED(device);

	auto store = val::global("localStorage");
	if (store.isNull())
		return false;

	const auto keyCount = store["length"].as<int>();
	for (auto i = 0; i < keyCount; ++i) {
		const auto key = store.call<std::string>("key", i);
		const auto value = store.call<val>("getItem", key).as<std::string>();
		map.insert(QString::fromStdString(key),
				   QString::fromStdString(value));
	}

	return true;
}

bool writeWasmSettings(QIODevice &device, const QSettings::SettingsMap &map)
{
	auto store = val::global("localStorage");
	if (store.isNull())
		return false;

	store.call<void>("clear");
	for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
		store.call<void>("setItem",
						 it.key().toStdString(),
						 it.value().toString().toStdString());
	}

	device.write(QUuid::createUuid().toByteArray());
	return true;
}

}

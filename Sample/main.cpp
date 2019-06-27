#include <QGuiApplication>
#include <QQmlApplicationEngine>
#ifdef Q_OS_WASM
#include <qwasmsettings.h>
#endif

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);
	QCoreApplication::setApplicationName(QStringLiteral("Sample"));
	QCoreApplication::setOrganizationName(QStringLiteral("Skycoder42"));
	QCoreApplication::setOrganizationDomain(QStringLiteral("de.skycoder42"));

#ifdef Q_OS_WASM
	QWasmSettings::registerFormat();
#endif

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}

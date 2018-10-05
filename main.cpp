#include <QElapsedTimer>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

#include "DragableImage.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

	QQuickView view;
	int totalDuration = 0;
	int loops = 0;
	QElapsedTimer timer;
	timer.start();
	QObject::connect(&view, &QQuickView::beforeRendering, [&]() {
	totalDuration += timer.elapsed();
	++loops;
		if (totalDuration > 10 * 1000) {
		qDebug() << (1000.0 * loops) / totalDuration << "fps";
		totalDuration = 0;
		loops = 0;
		}
	timer.restart();
	});

	qmlRegisterType<DragableImage>("DragImage", 1, 0, "DragableImage");

	view.setSource(QUrl(QLatin1String("qrc:/main.qml")));

	//	QQmlComponent component(view.engine());
	//	component.setData("import QtQuick 2.0\nText {}", QUrl());
	//	QQuickItem *childItem = qobject_cast<QQuickItem *>(component.create());

	//	if (childItem == nullptr) {
	//		qCritical() << component.errorString();
	//		return 0;
	//	}

	//	// Set the text of the QML item. It's possible to set all the properties
	//	// with this way.
	//	childItem->setProperty("text", "Hello dynamic object");
	//	childItem->setProperty("color", "white");
	//	// Put it into the root QML item
	//	childItem->setParentItem(view.rootObject());

	//	QQmlApplicationEngine engine;

	//	engine.load(QUrl(QLatin1String("qrc:/main.qml")));
	//	if (engine.rootObjects().isEmpty())
	//	return -1;
	view.show();
	return app.exec();
}

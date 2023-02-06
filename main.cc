#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "colorlinesmodel.h"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  qmlRegisterType<ColorLinesModel>("CLModel", 1, 0, "ColorLinesModel");

  QQmlApplicationEngine engine;
  const QUrl url(u"qrc:/ColorLines/components/Main.qml"_qs);
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}

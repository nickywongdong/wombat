#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include"forkbomb.h"
#include"datastuff.h"
#include <QQmlEngine>
#include <QtQml>


int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    qmlRegisterType<test>("forker.us",1,0,"Test");
    qmlRegisterType<DataStuff>("datastuff.us",1,0,"DataStuff");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

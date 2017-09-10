#include <cstdlib>
#include <ctime>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include "cpp/simplegamehandler.h"


void initialize_stuff(){
    std::srand(std::time(0));
}


int main(int argc, char *argv[])
{
    initialize_stuff();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QScopedPointer<SimpleGameHandler> game_handler(new SimpleGameHandler);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    engine.rootContext()->setContextProperty("game_handler", game_handler.data() );

    return app.exec();
}

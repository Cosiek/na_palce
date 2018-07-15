#include <cstdlib>
#include <ctime>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include "cpp/gamehandler.h"


void initialize_stuff(){
    std::srand(std::time(0));
}


int main(int argc, char *argv[])
{
    initialize_stuff();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QScopedPointer<GameHandler> game_handler(new GameHandler);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    engine.rootContext()->setContextProperty("game_handler", game_handler.data() );

    return app.exec();
}

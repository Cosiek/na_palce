#include <cstdlib>
#include <ctime>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include "cpp/gamehandler.h"
#include "cpp/settings.h"
#include "cpp/statistics_handler.h"


void initialize_stuff(){
    std::srand(std::time(0));
}


int main(int argc, char *argv[])
{
    initialize_stuff();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QScopedPointer<GameHandler> game_handler_ptr(new GameHandler);
    QScopedPointer<StatisticsHandler> stats_handler_ptr(new StatisticsHandler);
    QScopedPointer<SettingsHolder> settings_ptr(new SettingsHolder);

    GameHandler * game_handler = game_handler_ptr.data();
    StatisticsHandler * stats_handler = stats_handler_ptr.data();
    game_handler->stats = stats_handler;
    SettingsHolder * settings = settings_ptr.data();
    game_handler->settings = settings;

    engine.rootContext()->setContextProperty("game_handler", game_handler );
    engine.rootContext()->setContextProperty("stats_handler", stats_handler );
    engine.rootContext()->setContextProperty("settings", settings );

    return app.exec();
}

#include "simplegamehandler.h"
#include <unordered_map>


std::unordered_map<std::string, bool> pressed = {
    {"valve1", false},
    {"valve2", false},
    {"valve3", false}
};

SimpleGameHandler::SimpleGameHandler(QObject *parent) : QObject(parent)
{}

QString SimpleGameHandler::key_pressed(QString key_name)
{
    pressed[key_name.toUtf8().constData()] = true;
    for(auto iter=pressed.begin(); iter!=pressed.end(); iter++){
        auto cur = iter->first;
        qDebug() << cur.c_str() << " = " << pressed[cur];
    }
    return key_name + " pressed (C++)";
}

QString SimpleGameHandler::key_released(QString key_name)
{
    pressed[key_name.toUtf8().constData()] = false;
    qDebug() << pressed[key_name.toUtf8().constData()];
    return key_name + " released (C++)";
}

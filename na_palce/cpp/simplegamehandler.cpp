#include "simplegamehandler.h"

SimpleGameHandler::SimpleGameHandler(QObject *parent) : QObject(parent)
{}

QString SimpleGameHandler::key_pressed(QString key_name)
{
    return key_name + " pressed (C++)";
}

QString SimpleGameHandler::key_released(QString key_name)
{
    return key_name + " released (C++)";
}

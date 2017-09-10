#include <cstdlib>
#include <unordered_map>

#include "simplegamehandler.h"
#include "notes.h"

std::unordered_map<std::string, bool> pressed = {
    {"valve1", false},
    {"valve2", false},
    {"valve3", false}
};


NoteType get_random_note(){
    return NOTE_TYPES[std::rand() % 46];
}


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
    auto note = get_random_note();
    qDebug() << ">" << note.position << "< losowa";
    qDebug() << note.name.c_str() << " losowa";
    return key_name + " released (C++) ";
}

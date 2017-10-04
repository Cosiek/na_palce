#include <cstdlib>
#include <deque>
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

// Create a deque containing current notes
std::deque<NoteType> current_notes;

QString SimpleGameHandler::get_current_state(){
    QString note_names;
    for(NoteType nt : current_notes) {
        note_names.append(nt.name.c_str());
        note_names.append('+');
        note_names.append(std::to_string(nt.position).c_str());
        note_names.append(' ');
    }
    return note_names;
}

void SimpleGameHandler::set_state(){
    current_notes.clear();
    current_notes.push_back(get_random_note());
    current_notes.push_back(get_random_note());
}

SimpleGameHandler::SimpleGameHandler(QObject *parent) : QObject(parent)
{}

QString SimpleGameHandler::key_pressed(QString key_name)
{
    pressed[key_name.toUtf8().constData()] = true;
    for(auto iter=pressed.begin(); iter!=pressed.end(); iter++){
        auto cur = iter->first;
    }
    return key_name + " pressed (C++)";
}

QString SimpleGameHandler::key_released(QString key_name)
{
    pressed[key_name.toUtf8().constData()] = false;
    return key_name + " released (C++) ";
}

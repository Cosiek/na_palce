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

// Create a deque containing current notes
std::deque<Note> current_notes;

QString SimpleGameHandler::get_current_state(){
    QString note_names;
    for(Note note : current_notes) {
        note_names.append(note.type.name.c_str());
        note_names.append('+');
        note_names.append(std::to_string(note.type.position).c_str());
        note_names.append(' ');
    }
    return note_names;
}

void SimpleGameHandler::set_state(){
    current_notes.clear();
    current_notes.push_back(get_random_note(0, 46));
    current_notes.push_back(get_random_note(0, 46));
}

void changeNote(){
    current_notes.pop_front();
    current_notes.push_back(get_random_note(0, 46));
}

SimpleGameHandler::SimpleGameHandler(QObject *parent) : QObject(parent)
{}


void checkNote(std::string key, bool isPressed){
    // compare current keys state with what current note type state
    if (current_notes.front().match(pressed)){
        // if correct, get new random note,
        changeNote();
    // if not, check if step in right dirrection
    } else if (!current_notes.front().isMistake(key, isPressed)){
        // if change not in right direction, mark error
        qDebug() << "BŁĄD " << key.c_str();
        // TODO increase mistakes counter
    }
}


QString SimpleGameHandler::key_pressed(QString key_name)
{
    std::string key = key_name.toUtf8().constData();
    // set keys state
    pressed[key] = true;
    checkNote(key, true);
    return key_name + " pressed (C++)";
}

QString SimpleGameHandler::key_released(QString key_name)
{
    std::string key = key_name.toUtf8().constData();
    // set keys state
    pressed[key] = false;
    checkNote(key, false);
    return key_name + " released (C++) ";
}

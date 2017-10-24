#include <cstdlib>
#include <deque>
#include <unordered_map>

#include <QObject>
#include <QtQuick>

#include "simplegamehandler.h"
#include "notes.h"


SimpleGameHandler::SimpleGameHandler(QObject *parent) : QObject(parent)
{
    // currently pressed keys
    this->pressed = {
        {"valve1", false},
        {"valve2", false},
        {"valve3", false}
    };
    // A timer to check if player kept valves in right position
    // if two subseqent notes have the same setting
    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(checkNoteSlot()));
    // initialize notes
    this->set_state();
}

void SimpleGameHandler::set_state(){
    this->current_notes.clear();
    this->current_notes.push_back(get_random_note(0, 46));
    this->current_notes.push_back(get_random_note(0, 46));
}

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


void SimpleGameHandler::changeNote(){
    this->current_notes.pop_front();
    this->current_notes.push_back(get_random_note(0, 46));
}


void SimpleGameHandler::checkNote(std::string key, bool isPressed){
    // no matter what is the reason for this function to run
    // it should stop the timer anyway.
    timer->stop();
bool SimpleGameHandler::checkNoteSlot(){
    this->timer->stop();
    // compare current keys state with what current note type state
    if (current_notes.front().match(pressed)){
        // if correct, get new random note,
        changeNote();
        // new note might be using the same setting - use a timer
        // to check if user havent moved
        if (current_notes.front().match(pressed)){
            timer->start(1000);
        }
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


void SimpleGameHandler::debugHelper(){
    qDebug() << "debugHelper ";
}

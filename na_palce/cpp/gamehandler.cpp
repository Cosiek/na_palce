#include <cstdlib>
#include <deque>
#include <unordered_map>

#include <QObject>
#include <QtQuick>

#include "gamehandler.h"
#include "notes.h"


GameHandler::GameHandler(QObject *parent) : QObject(parent)
{
    // currently pressed keys
    this->pressed = {
        {"valve1", false},
        {"valve2", false},
        {"valve3", false}
    };
    // A timer to check if player kept valves in right position
    // if two subseqent notes have the same setting
    this->same_note_timer = new QTimer();
    connect(this->same_note_timer, SIGNAL(timeout()), this, SLOT(same_note_timeout()));
    // A timer to keep track of game time
    this->tick_timer = new QTimer();
    connect(this->tick_timer, SIGNAL(timeout()), this, SLOT(game_tick_timeout()));
}

/*
 * Interface functions --------------------------------------------------------
 */

void GameHandler::init_new_game(){
    this->pressed = {{"valve1", false}, {"valve2", false}, {"valve3", false}};
    this->current_notes.clear();
    Note note = get_random_note(0, 45);
    while (note.match(this->pressed)) {
        note = get_random_note(0, 45);
    }
    this->current_notes.push_back(note);
    this->current_notes.push_back(get_random_note(0, 45));
    this->state = QString("pending");
    this->time_left = 60;
}

QString GameHandler::get_current_state(){
    QJsonObject stateObject;
    stateObject.insert("state", QJsonValue::fromVariant(this->state));
    stateObject.insert("time_left", QJsonValue::fromVariant(this->time_left));

    QJsonDocument jsonDocument = QJsonDocument(stateObject);
    return jsonDocument.toJson();
}

QString GameHandler::get_current_notes(){
    QJsonArray notesArray;
    for(Note note : current_notes) {
        notesArray.append(note.toQJsonObject());
    }

    QJsonDocument jsonDocument = QJsonDocument(notesArray);
    return jsonDocument.toJson();
}

QString GameHandler::key_pressed(QString key_name)
{
    std::string key = key_name.toUtf8().constData();
    // set keys state
    pressed[key] = true;
    check_key_change(key, true);
    return key_name + " pressed (C++)";
}

QString GameHandler::key_released(QString key_name)
{
    std::string key = key_name.toUtf8().constData();
    // set keys state
    pressed[key] = false;
    check_key_change(key, false);
    return key_name + " released (C++) ";
}

void GameHandler::exit_game(){
    this->same_note_timer->stop();
    this->tick_timer->stop();
}

/*
 * Signals --------------------------------------------------------------------
 */

void GameHandler::same_note_timeout(){
    this->check_note();
    emit same_note_signal();
}

void GameHandler::game_tick_timeout(){
    this->time_left -= 1;
    if (this->time_left == 0){
        this->tick_timer->stop();
        this->state = QString("stoped");
    }
    emit game_tick_signal();
}

/*
 * Private functions ----------------------------------------------------------
 */

void GameHandler::check_key_change(std::string key, bool isPressed){
    // compare current keys state with what current note type state
    if (! this->tick_timer->isActive()){
        this->state = QString("running");
        this->tick_timer->start(1000);
    }
    if (this->check_note()){
        // if correct, get new random note,
        qDebug() << "DOBRZE " << key.c_str();
    // if not, check if step in right dirrection
    } else if (this->current_notes.front().isMistake(key, isPressed)){
        // if change not in right direction, mark error
        qDebug() << "BŁĄD " << key.c_str();
        // TODO increase mistakes counter
    }
}

void GameHandler::change_note(){
    this->current_notes.pop_front();
    this->current_notes.push_back(get_random_note(0, 45));
}

bool GameHandler::check_note(){
    // no matter what is the reason for this function to run
    // it should stop the timer anyway.
    this->same_note_timer->stop();
    // compare current keys state with what current note type state
    if (this->current_notes.front().match(this->pressed)){
        // if correct, get new random note,
        this->change_note();
        // new note might be using the same setting - use a timer
        // to check if user havent moved
        if (this->current_notes.front().match(this->pressed)){
            this->same_note_timer->start(1000);
        }
        return true;
    }
    return false;
}

void GameHandler::debug_helper(){
    qDebug() << "debug_helper ";
}

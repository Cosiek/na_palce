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
    this->timer = new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(callTimeout()));
    // A timer to keep track of game time
    this->gameTimer = new QTimer();
    connect(this->gameTimer, SIGNAL(timeout()), this, SLOT(callGameTimeout()));
}

void GameHandler::init_new_game(){
    this->current_notes.clear();
    this->current_notes.push_back(get_random_note(0, 45));
    this->current_notes.push_back(get_random_note(0, 45));
}

QString GameHandler::get_current_state(){
    QJsonArray jsonArray;
    for(Note note : current_notes) {
        jsonArray.append(note.toQJsonObject());
    }
    QJsonDocument jsonDocument = QJsonDocument(jsonArray);
    return jsonDocument.toJson();
}


void GameHandler::changeNote(){
    this->current_notes.pop_front();
    this->current_notes.push_back(get_random_note(0, 45));
}


void GameHandler::checkKeyChange(std::string key, bool isPressed){
    // compare current keys state with what current note type state
    if (! this->gameTimer->isActive()){
        this->gameTimer->start(60000);
    }
    if (this->checkNote()){
        // if correct, get new random note,
        qDebug() << "DOBRZE " << key.c_str();
    // if not, check if step in right dirrection
    } else if (this->current_notes.front().isMistake(key, isPressed)){
        // if change not in right direction, mark error
        qDebug() << "BŁĄD " << key.c_str();
        // TODO increase mistakes counter
    }
}

bool GameHandler::checkNote(){
    // no matter what is the reason for this function to run
    // it should stop the timer anyway.
    this->timer->stop();
    // compare current keys state with what current note type state
    if (this->current_notes.front().match(this->pressed)){
        // if correct, get new random note,
        this->changeNote();
        // new note might be using the same setting - use a timer
        // to check if user havent moved
        if (this->current_notes.front().match(this->pressed)){
            this->timer->start(1000);
        }
        return true;
    }
    return false;
}


void GameHandler::callTimeout(){
    this->checkNote();
    emit timeout();
}


void GameHandler::callGameTimeout(){
    this->gameTimer->stop();
    emit gameTimeout();
}


QString GameHandler::key_pressed(QString key_name)
{
    std::string key = key_name.toUtf8().constData();
    // set keys state
    pressed[key] = true;
    checkKeyChange(key, true);
    return key_name + " pressed (C++)";
}

QString GameHandler::key_released(QString key_name)
{
    std::string key = key_name.toUtf8().constData();
    // set keys state
    pressed[key] = false;
    checkKeyChange(key, false);
    return key_name + " released (C++) ";
}


void GameHandler::debugHelper(){
    qDebug() << "debugHelper ";
}

#include <cstdlib>
#include <deque>
#include <unordered_map>

#include <QObject>
#include <QtQuick>

#include "gamehandler.h"
#include "notes.h"
#include "statistics_handler.h"


static int SAME_NOTE_INTERVAL = 1000;


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

    this->note_timestamp = 0;

    this->stats->reset();
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

QString GameHandler::get_note_types(){
    QJsonArray noteTypesArray;
    for(NoteType noteType : NOTE_TYPES) {
        noteTypesArray.append(noteType.toQJsonObject());
    }

    QJsonDocument jsonDocument = QJsonDocument(noteTypesArray);
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
    if (this->check_note()){
        // update stats
        this->stats->countCorrect(this->current_notes.front(), SAME_NOTE_INTERVAL);
        this->change_note();
        emit onCorrect();
    } else {
        emit onMistake();
    }
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
    // start a timer, if it isn't runing yet
    if (! this->tick_timer->isActive() && this->state == QString("pending")){
        this->state = QString("running");
        this->tick_timer->start(1000);
    }
    // set note timestamp if it isn't already
    if (this->note_timestamp == 0){
        this->note_timestamp = QDateTime::currentMSecsSinceEpoch();
    }
    // compare current keys state with what current note type state
    if (this->check_note()){  // if correct...;
        // handle calculating note press time
        qint64 delta = QDateTime::currentMSecsSinceEpoch() - this->note_timestamp;
        this->note_timestamp += delta;

        // update stats
        this->stats->countCorrect(this->current_notes.front(), delta);

        // get new random note
        this->change_note();
        emit onCorrect();
    // if not, check if step in right dirrection
    } else if (this->current_notes.front().isMistake(key, isPressed)){
        // if change not in right direction, mark error
        this->stats->countMistake(this->current_notes.front());
        emit onMistake();
    }
}

void GameHandler::change_note(){
    this->current_notes.pop_front();
    this->current_notes.push_back(get_random_note(0, 45));
    // new note might be using the same setting - use a timer
    // to check if user havent moved
    if (this->current_notes.front().match(this->pressed)){
        this->same_note_timer->start(SAME_NOTE_INTERVAL);
    }
}

bool GameHandler::check_note(){
    // no matter what is the reason for this function to run
    // it should stop the timer anyway.
    this->same_note_timer->stop();
    // compare current keys state with what current note type state
    return (this->current_notes.front().match(this->pressed));
}

void GameHandler::debug_helper(){
    qDebug() << "debug_helper ";
}

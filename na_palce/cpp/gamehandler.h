#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <deque>
#include <unordered_map>

#include <QDebug>
#include <QObject>
#include <QTimer>

#include "notes.h"
#include "settings.h"
#include "statistics_handler.h"


class GameHandler: public QObject
{
    Q_OBJECT
public:
    explicit GameHandler(QObject *parent = nullptr);

    Q_INVOKABLE void init_new_game();
    Q_INVOKABLE QString get_current_state();
    Q_INVOKABLE QString get_current_notes();
    Q_INVOKABLE QString get_note_types();
    Q_INVOKABLE QString key_pressed(QString);
    Q_INVOKABLE QString key_released(QString);
    Q_INVOKABLE void exit_game();

    // references to other complex objects
    StatisticsHandler * stats;
    SettingsHolder * settings;
private:
    void change_note();
    void check_key_change(std::string, bool);
    // a deque containing current notes
    std::deque<Note> current_notes;
    // available states: "pending", "running", "stopped"
    QString state;
    // currently pressed keys
    std::unordered_map<std::string, bool> pressed;
    // A timer to check if player kept valves in right position
    // if two subseqent notes have the same setting
    QTimer * same_note_timer;
    // A timer to check game duration time
    QTimer * tick_timer;
    int time_left;

    qint64 note_timestamp;
private slots:
    bool check_note();
    void debug_helper();  // TODO: remove from final version
    void same_note_timeout();
    void game_tick_timeout();
signals:
    void same_note_signal();
    void game_tick_signal();
    void onMistake();
    void onCorrect();
};

#endif // GAMEHANDLER_H

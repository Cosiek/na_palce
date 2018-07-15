#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <deque>
#include <unordered_map>

#include <QDebug>
#include <QObject>
#include <QTimer>

#include "notes.h"


class GameHandler: public QObject
{
    Q_OBJECT
public:
    explicit GameHandler(QObject *parent = nullptr);

    Q_INVOKABLE QString get_current_state();
    Q_INVOKABLE QString key_pressed(QString);
    Q_INVOKABLE QString key_released(QString);
    Q_INVOKABLE void set_state();
private:
    void changeNote();
    void checkKeyChange(std::string, bool);
    // a deque containing current notes
    std::deque<Note> current_notes;
    // currently pressed keys
    std::unordered_map<std::string, bool> pressed;
    // A timer to check if player kept valves in right position
    // if two subseqent notes have the same setting
    QTimer * timer;
    // A timer to check game duration time
    QTimer * gameTimer;
private slots:
    bool checkNote();
    // TODO: remove from final version
    void debugHelper();
    void callTimeout();
    void callGameTimeout();
signals:
    void timeout();
    void gameTimeout();
};

#endif // GAMEHANDLER_H
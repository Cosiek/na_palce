#ifndef SIMPLEGAMEHANDLER_H
#define SIMPLEGAMEHANDLER_H

#include <deque>
#include <unordered_map>

#include <QDebug>
#include <QObject>
#include <QTimer>

#include "notes.h"


class SimpleGameHandler: public QObject
{
    Q_OBJECT
public:
    explicit SimpleGameHandler(QObject *parent = nullptr);

    Q_INVOKABLE QString get_current_state();
    Q_INVOKABLE QString key_pressed(QString);
    Q_INVOKABLE QString key_released(QString);
private:
    void set_state();
    void changeNote();
    void checkNote(std::string, bool);
    // a deque containing current notes
    std::deque<Note> current_notes;
    // currently pressed keys
    std::unordered_map<std::string, bool> pressed;
    // A timer to check if player kept valves in right position
    // if two subseqent notes have the same setting
    QTimer * timer;
private slots:
    bool checkNoteSlot();
    // TODO: remove from final version
    void debugHelper();
};

#endif // SIMPLEGAMEHANDLER_H

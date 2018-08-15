#ifndef STATISTICS_HANDLER_H
#define STATISTICS_HANDLER_H

#include "map"

#include <QObject>

#include "notes.h"


struct NoteStatistic{
    NoteType * note;
    unsigned long avgTime;
    int mistakesCount;
    int playedCount;
};


class StatisticsHandler: public QObject
{
    Q_OBJECT
public:
    explicit StatisticsHandler(QObject *parent = nullptr);

    Q_INVOKABLE QString get_stats();

    void countCorrect(Note, qint64);
    void countMistake(Note);
    void reset();
private:
    std::map<QString, NoteStatistic> notesStats;
    int total_mistakes;
    int total_played;
};

#endif // STATISTICS_HANDLER_H

#ifndef STATISTICS_HANDLER_H
#define STATISTICS_HANDLER_H

#include "map"

#include <QObject>

#include "notes.h"


struct NoteStatistic{
    NoteType * note;
    int mistakesCount;
};


class StatisticsHandler: public QObject
{
    Q_OBJECT
public:
    explicit StatisticsHandler(QObject *parent = nullptr);

    Q_INVOKABLE QString get_stats();

    void countMistake(Note);
    void reset();
private:
    std::map<QString, NoteStatistic> notesStats;
    int total_mistakes;
};

#endif // STATISTICS_HANDLER_H

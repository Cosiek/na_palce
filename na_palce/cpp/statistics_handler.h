#ifndef STATISTICS_HANDLER_H
#define STATISTICS_HANDLER_H

#include <QObject>


class StatisticsHandler: public QObject
{
    Q_OBJECT
public:
    explicit StatisticsHandler(QObject *parent = nullptr);

    Q_INVOKABLE QString get_stats();
};

#endif // STATISTICS_HANDLER_H

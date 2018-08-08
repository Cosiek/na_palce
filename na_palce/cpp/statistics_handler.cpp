#include <QObject>

#include "statistics_handler.h"

StatisticsHandler::StatisticsHandler(QObject *parent) : QObject(parent)
{
    this->mistakes = 0;
}

QString StatisticsHandler::get_stats(){
    return QString::number(this->mistakes);
}


void StatisticsHandler::countMistake(){
    this->mistakes++;
}

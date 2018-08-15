#include <QObject>

#include "statistics_handler.h"

StatisticsHandler::StatisticsHandler(QObject *parent) : QObject(parent)
{
    this->reset();
}

void StatisticsHandler::reset(){
    this->total_mistakes = 0;
}

QString StatisticsHandler::get_stats(){
    return QString::number(this->total_mistakes);
}


void StatisticsHandler::countMistake(){
    this->total_mistakes++;
}

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
    QJsonObject statsObject;
    statsObject["total_mistakes"] = this->total_mistakes;
    QJsonDocument jsonDocument = QJsonDocument(statsObject);
    return jsonDocument.toJson();
}


void StatisticsHandler::countMistake(){
    this->total_mistakes++;
}

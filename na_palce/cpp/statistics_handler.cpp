#include <QObject>

#include "statistics_handler.h"

StatisticsHandler::StatisticsHandler(QObject *parent) : QObject(parent)
{

}

QString StatisticsHandler::get_stats(){
    return "Damn!";
}

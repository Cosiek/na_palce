#include <array>

#include <QObject>
#include <QtQuick>

#include "notes.h"
#include "statistics_handler.h"


StatisticsHandler::StatisticsHandler(QObject *parent) : QObject(parent)
{
    for (unsigned int idx = 0; idx < NOTE_TYPES.size(); idx++){
        NoteType note_type = NOTE_TYPES[idx];
        this->notesStats[note_type.getId()] = NoteStatistic{&note_type, 0, 0};
    }
    this->reset();
}


void StatisticsHandler::reset(){
    this->total_mistakes = 0;

    for(auto const &ent : this->notesStats) {
        notesStats[ent.first].mistakesCount = 0;
    }
}


QString StatisticsHandler::get_stats(){
    QJsonObject statsObject;
    statsObject["total_mistakes"] = this->total_mistakes;

    QJsonObject notesJson;
    NoteStatistic stat;
    for(auto const& ent : this->notesStats) {
        stat = ent.second;
        notesJson[ent.first] = stat.mistakesCount;
    }
    statsObject["notes"] = notesJson;

    QJsonDocument jsonDocument = QJsonDocument(statsObject);
    return jsonDocument.toJson();
}


void StatisticsHandler::countMistake(Note note){
    this->total_mistakes++;
    this->notesStats[note.noteType.getId()].mistakesCount++;
}

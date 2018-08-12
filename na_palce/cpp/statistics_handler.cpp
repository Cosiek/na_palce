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
    this->total_played = 0;

    for(auto const &ent : this->notesStats) {
        notesStats[ent.first].mistakesCount = 0;
        notesStats[ent.first].playedCount = 0;
    }
}


QString StatisticsHandler::get_stats(){
    QJsonObject statsObject;
    statsObject["total_mistakes"] = this->total_mistakes;
    statsObject["total_played"] = this->total_played;

    QJsonObject notesJson;
    for(auto const& ent : this->notesStats) {
        QJsonObject noteJson;
        noteJson["mistakes_count"] = ent.second.mistakesCount;
        noteJson["played_count"] = ent.second.playedCount;
        notesJson[ent.first] = noteJson;
    }
    statsObject["notes"] = notesJson;

    QJsonDocument jsonDocument = QJsonDocument(statsObject);
    return jsonDocument.toJson();
}


void StatisticsHandler::countMistake(Note note){
    this->total_mistakes++;
    this->notesStats[note.noteType.getId()].mistakesCount++;
}


void StatisticsHandler::countCorrect(Note note){
    this->total_played++;
    this->notesStats[note.noteType.getId()].playedCount++;
}

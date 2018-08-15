#include <array>

#include <QObject>
#include <QtQuick>

#include "notes.h"
#include "statistics_handler.h"


StatisticsHandler::StatisticsHandler(QObject *parent) : QObject(parent)
{
    for (unsigned int idx = 0; idx < NOTE_TYPES.size(); idx++){
        NoteType note_type = NOTE_TYPES[idx];
        this->notesStats[note_type.getId()] = NoteStatistic{&note_type, 0, 0, 0};
    }
    this->reset();
}


void StatisticsHandler::reset(){
    this->total_mistakes = 0;
    this->total_played = 0;
    this->avgTime = 0;

    for(auto const &ent : this->notesStats) {
        notesStats[ent.first].mistakesCount = 0;
        notesStats[ent.first].playedCount = 0;
        notesStats[ent.first].avgTime = 0;
    }
}


QString StatisticsHandler::get_stats(){
    QJsonObject statsObject;
    statsObject["total_mistakes"] = this->total_mistakes;
    statsObject["total_played"] = this->total_played;
    statsObject["avg_time"] = QString::number(this->avgTime);

    QJsonObject notesJson;
    for(auto const& ent : this->notesStats) {
        QJsonObject noteJson;
        noteJson["mistakes_count"] = ent.second.mistakesCount;
        noteJson["played_count"] = ent.second.playedCount;
        noteJson["avg_time"] = QString::number(ent.second.avgTime);
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


void StatisticsHandler::countCorrect(Note note, qint64 noteTime){
    // update note type statistics
    QString key = note.noteType.getId();
    unsigned long avgTime = (this->notesStats[key].avgTime * this->notesStats[key].playedCount + noteTime) / (this->notesStats[key].playedCount + 1);
    this->notesStats[key].playedCount++;
    this->notesStats[key].avgTime = avgTime;

    // update general statistics
    this->avgTime = (this->avgTime * this->total_played + noteTime) / (this->total_played + 1);
    this->total_played++;
}

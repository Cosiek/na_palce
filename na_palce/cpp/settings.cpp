#include <string>

#include <QFile>

#include "settings.h"

const QString SETTINGS_FILE_PTH = "na_palce_settings.json";


SettingsHolder::SettingsHolder(QObject *parent) : QObject(parent)
{
    this->displayNoteNames = true;


bool SettingsHolder::saveSettings(){
    QFile saveFile(SETTINGS_FILE_PTH);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    QByteArray settingsJson = this->toJson();

    saveFile.write(settingsJson);
    return true;
}

bool SettingsHolder::loadSettingsFromFile(){
    QFile loadFile(SETTINGS_FILE_PTH);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray settingsData = loadFile.readAll();
    this->loadSettingsFromJson(settingsData);

    return true;
}

void SettingsHolder::loadSettingsFromJson(QByteArray settingsData){
    QJsonDocument jsonDocument(QJsonDocument::fromJson(settingsData));
    jsonDocument.object();

    this->displayNoteNames = jsonDocument["displayNoteNames"].toBool();
}

QByteArray SettingsHolder::toJson(){
    QJsonObject settingsObject;
    settingsObject["displayNoteNames"] = this->displayNoteNames;

    QJsonDocument jsonDocument = QJsonDocument(settingsObject);
    return jsonDocument.toJson();
}

#include <string>

#include <QDir>
#include <QFile>
#include <QGuiApplication>

#include "settings.h"


SettingsHolder::SettingsHolder(QObject *parent) : QObject(parent)
{
    this->displayNoteNames = true;

    // get file path
    QString dirPath = QCoreApplication::applicationDirPath();
    QString fileName = QString("na_palce_settings.json");
    this->SETTINGS_FILE_PTH += QDir(dirPath).filePath(fileName);
    // read settings from file
    this->loadSettingsFromFile();
    // write settings to the same file (in case any keys were added)
    this->saveSettings();
}


bool SettingsHolder::saveSettings(){
    QFile saveFile(this->SETTINGS_FILE_PTH);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    QByteArray settingsJson = this->toJson();

    saveFile.write(settingsJson);
    return true;
}

bool SettingsHolder::loadSettingsFromFile(){
    QFile loadFile(this->SETTINGS_FILE_PTH);

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

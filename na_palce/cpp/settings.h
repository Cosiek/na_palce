#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

class SettingsHolder: public QObject
{
    Q_OBJECT
public:
    explicit SettingsHolder(QObject *parent = nullptr);
    // actual settings
    bool displayNoteNames;

    // some helper methods
    Q_INVOKABLE bool saveSettings();
    Q_INVOKABLE bool loadSettingsFromFile();
    Q_INVOKABLE void loadSettingsFromJson(QByteArray);
    Q_INVOKABLE QByteArray toJson();
};

#endif // SETTINGS_H

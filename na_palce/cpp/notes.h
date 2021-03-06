#ifndef NOTES_H
#define NOTES_H

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

struct keys_state{
    bool valve1, valve2, valve3;
};

class NoteType{
public:
    NoteType(int, int, std::string, keys_state, bool, bool);
    int id;
    int position;
    std::string name;
    keys_state keys;
    bool sharp, flat;
    bool match(std::unordered_map<std::string, bool>);
    bool isMistake(std::string, bool);
    std::vector<NoteType> getNotesByKeys(std::unordered_map<std::string, bool>);
    QString getId();
    QJsonObject toQJsonObject();
};

class Note
{
public:
    int length;
    NoteType noteType;
    bool match(std::unordered_map<std::string, bool>);
    bool isMistake(std::string, bool);
    QJsonObject toQJsonObject();
};

extern Note get_random_note(int, int);

extern const std::array<NoteType, 45> NOTE_TYPES;

#endif // NOTES_H

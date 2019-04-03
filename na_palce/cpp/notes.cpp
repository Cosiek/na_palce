#include <array>
#include <string>
#include <unordered_map>
#include <vector>

#include <QJsonObject>

#include "notes.h"


// ============================================================================
// Note Type ------------------------------------------------------------------

NoteType::NoteType(int id_, int pos, std::string name_, keys_state keys_,
                   bool sharp_, bool flat_){
    id = id_;
    position = pos;
    name = name_;
    keys = keys_;
    sharp = sharp_;
    flat = flat_;
}

// Notes definitions ----------------------------------------------------------

extern const std::array<NoteType, 45> NOTE_TYPES = {
    NoteType(1, -4, "#F", {true, true, true}, true, false),
    NoteType(2, -3, "bG", {true, true, true}, false, true),
    NoteType(3, -3, "G", {true, false, true}, false, false),
    NoteType(4, -3, "#G", {false, true, true}, true, false),
    NoteType(5, -2, "bA",  {false, true, true}, false, true),
    NoteType(6, -2, "A", {true, true, false}, false, false),
    NoteType(7, -2, "#A", {true, false, false}, true, false),
    NoteType(8, -1, "bB", {true, false, false}, false, true),
    NoteType(9, -1, "B", {false, true, false}, false, false),
    NoteType(10, 0, "C", {false, false, false}, false, false),
    NoteType(11, 0, "#C", {true, true, true}, true, false),
    NoteType(12, 1, "bD", {true, true, true}, false, true),
    NoteType(13, 1, "D", {true, false, true}, false, false),
    NoteType(14, 1, "#D", {false, true, true}, true, false),
    NoteType(15, 2, "bE", {false, true, true}, false, true),
    NoteType(16, 2, "E", {true, true, false}, false, false),
    NoteType(17, 3, "F", {true, false, false}, false, false),
    NoteType(18, 3, "#F", {false, true, false}, true, false),
    NoteType(19, 4, "bG", {false, true, false}, false, true),
    NoteType(20, 4, "G", {false, false, false}, false, false),
    NoteType(21, 4, "#G", {false, true, true}, true, false),
    NoteType(22, 5, "bA", {false, true, true}, false, true),
    NoteType(23, 5, "A", {true, true, false}, false, false),
    NoteType(24, 5, "#A", {true, false, false}, true, false),
    NoteType(25, 6, "bB", {true, false, false}, false, true),
    NoteType(26, 6, "B", {false, true, false}, false, false),
    NoteType(27, 6, "#B", {false, false, false}, true, false),
    NoteType(28, 7, "C", {false, false, false}, false, false),
    NoteType(29, 7, "#C", {true, true, false}, true, false),
    NoteType(30, 8, "bD", {true, true, false}, false, true),
    NoteType(31, 8, "D", {true, false, false}, false, false),
    NoteType(32, 8, "#D", {false, true, false}, true, false),
    NoteType(33, 9, "bE", {false, true, false}, false, true),
    NoteType(34, 9, "E", {false, false, false}, false, false),
    NoteType(35, 10, "F", {true, false, false}, false, false),
    NoteType(36, 10, "#F", {false, true, false}, true, false),
    NoteType(37, 11, "bG", {false, true, false}, false, true),
    NoteType(38, 11, "G", {false, false, false}, false, false),
    NoteType(39, 11, "#G", {false, true, true}, true, false),
    NoteType(40, 12, "bA", {false, true, true}, false, true),
    NoteType(41, 12, "A", {true, true, false}, false, false),
    NoteType(42, 12, "#A", {true, false, false}, true, false),
    NoteType(43, 13, "bB", {true, false, false}, false, true),
    NoteType(44, 13, "B", {false, true, false}, false, false),
    NoteType(45, 14, "C", {false, false, false}, false, false),
};


bool NoteType::match(std::unordered_map<std::string, bool> keys){
    return (this->keys.valve1 == keys["valve1"] &&
            this->keys.valve2 == keys["valve2"] &&
            this->keys.valve3 == keys["valve3"]);
}


bool NoteType::isMistake(std::string valve, bool isPressed){
    if (valve == "valve1"){
        return this->keys.valve1 != isPressed;
    } else if (valve == "valve2"){
        return this->keys.valve2 != isPressed;
    } else if (valve == "valve3"){
        return this->keys.valve3 != isPressed;
    }
    return true;
}


std::vector<NoteType> NoteType::getNotesByKeys(
        std::unordered_map<std::string, bool> pressed){
    std::vector<NoteType> v = {};
    unsigned int i = 0;
    while (i < NOTE_TYPES.size()) {
        NoteType note_type = NOTE_TYPES[i];
        if (note_type.match(pressed)){v.push_back(note_type);}
        i++;
    }
    return v;
}


QString NoteType::getId(){
    return QString::number(this->position) + ":" + this->name.c_str();
}


QJsonObject NoteType::toQJsonObject(){
    QJsonObject json;
    json["id"] = id;
    json["name"] = name.c_str();
    json["position"] = position;
    json["sharp"] = sharp;
    json["flat"] = flat;
    json["valve1"] = keys.valve1;
    json["valve2"] = keys.valve2;
    json["valve3"] = keys.valve3;
    return json;
}

// ============================================================================
// Note lenghth ---------------------------------------------------------------

const std::vector<int> LENGTHS = {1, 2, 4, 8, 16};

// ============================================================================
// Note (combined) ------------------------------------------------------------

Note get_random_note(int min, int max){
    int length;
    length = LENGTHS[std::rand() % 4];
    NoteType noteType = NOTE_TYPES[std::rand() % (max - min) + min];
    Note note = {length, noteType};
    return note;
}


bool Note::match(std::unordered_map<std::string, bool> keys){
    return this->noteType.match(keys);
}


bool Note::isMistake(std::string valve, bool isPressed){
    return this->noteType.isMistake(valve, isPressed);
}


QJsonObject Note::toQJsonObject(){
    QJsonObject json;
    json["length"] = length;
    json["name"] = noteType.name.c_str();
    json["type_id"] = noteType.id;
    json["position"] = noteType.position;
    json["sharp"] = noteType.sharp;
    json["flat"] = noteType.flat;
    json["valve1"] = noteType.keys.valve1;
    json["valve2"] = noteType.keys.valve2;
    json["valve3"] = noteType.keys.valve3;
    return json;
}

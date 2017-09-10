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
    int position;
    std::string name;
    keys_state keys;
    bool sharp, flat;
    NoteType(int, std::string, keys_state, bool, bool);
    bool match(std::unordered_map<std::string, bool>);
    std::vector<NoteType> getNotesByKeys(std::unordered_map<std::string, bool>);
};

extern const std::array<NoteType, 45> NOTE_TYPES;

#endif // NOTES_H

#include <string>

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
};

NoteType::NoteType(int pos, std::string name, keys_state keys, bool sharp, bool flat){
    position = pos;
    name = name;
    keys = keys;
    sharp = sharp;
    flat = flat;
}

const NoteType note_types [] = {};

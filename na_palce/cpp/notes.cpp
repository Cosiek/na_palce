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

NoteType::NoteType(int pos, std::string name, keys_state keys, bool sharp,
                   bool flat){
    position = pos;
    name = name;
    keys = keys;
    sharp = sharp;
    flat = flat;
}

// Notes definitions ----------------------------------------------------------

const NoteType NOTE_TYPES [] = {
    NoteType(-4, "#F", {true, true, true}, true, false),
    NoteType(-3, "bG", {true, true, true}, false, true),
    NoteType(-3, "G", {true, false, true}, false, false),
    NoteType(-3, "#G", {false, true, true}, true, false),
    NoteType(-2, "bA",  {false, true, true}, false, true),
    NoteType(-2, "A", {true, true, false}, false, false),
    NoteType(-2, "#A", {true, false, false}, true, false),
    NoteType(-1, "bB", {true, false, false}, false, true),
    NoteType(-1, "B", {false, true, false}, false, false),
    NoteType(0, "C", {false, false, false}, false, false),
    NoteType(0, "#C", {true, true, true}, true, false),
    NoteType(1, "bD", {true, true, true}, false, true),
    NoteType(1, "D", {true, false, true}, false, false),
    NoteType(1, "#D", {false, true, true}, true, false),
    NoteType(2, "bE", {false, true, true}, false, true),
    NoteType(2, "E", {true, true, false}, false, false),
    NoteType(3, "F", {true, false, false}, false, false),
    NoteType(3, "#F", {false, true, false}, false, true),
    NoteType(4, "bG", {false, true, false}, false, true),
    NoteType(4, "G", {false, false, false}, false, false),
    NoteType(4, "#G", {false, true, true}, true, false),
    NoteType(5, "bA", {false, true, true}, false, true),
    NoteType(5, "A", {true, true, false}, false, false),
    NoteType(5, "#A", {true, false, false}, true, false),
    NoteType(6, "bB", {true, false, false}, false, true),
    NoteType(6, "B", {false, true, false}, false, false),
    NoteType(6, "#B", {false, false, false}, true, false),
    NoteType(7, "C", {false, false, false}, false, false),
    NoteType(7, "#C", {true, true, false}, true, false),
    NoteType(8, "bD", {true, true, false}, false, true),
    NoteType(8, "D", {true, false, false}, false, false),
    NoteType(8, "#D", {false, true, false}, true, false),
    NoteType(9, "bE", {false, true, false}, false, true),
    NoteType(9, "E", {false, false, false}, false, false),
    NoteType(10, "F", {true, false, false}, false, false),
    NoteType(10, "#F", {false, true, false}, true, false),
    NoteType(11, "bG", {false, true, false}, false, true),
    NoteType(11, "G", {false, false, false}, false, false),
    NoteType(11, "#G", {false, true, true}, true, false),
    NoteType(12, "bA", {false, true, true}, false, true),
    NoteType(12, "A", {true, true, false}, false, false),
    NoteType(12, "#A", {true, false, false}, true, false),
    NoteType(13, "bB", {true, false, false}, false, true),
    NoteType(13, "B", {false, true, false}, false, false),
    NoteType(14, "C", {false, false, false}, false, false),
};

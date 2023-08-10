#include "tiletypes.h"

vector<int> tiletypes::MAP_OLD_TYPE_TO_NEW_TYPE(num_ingame_tile_types, 0);
vector<string> tiletypes::MAP_NEW_TYPE_TO_CHAR(num_ingame_tile_types, "");
const string tiletypes::hacky_debug_chars = ".0123456789ABCDEFGHIJKLMNPQRSTUVWX";
vector<int> tiletypes::XFORM_INVERT(num_ingame_tile_types, 0);
vector<int> tiletypes::XFORM_ROTCW(num_ingame_tile_types, 0);
vector<int> tiletypes::XFORM_ROTCCW(num_ingame_tile_types, 0);
vector<int> tiletypes::XFORM_FLIPH(num_ingame_tile_types, 0);
vector<int> tiletypes::XFORM_FLIPV(num_ingame_tile_types, 0);

int tiletypes::GetTypeFromChar(int charIndex) {
    return MAP_OLD_TYPE_TO_NEW_TYPE[charIndex];
}

char tiletypes::GetDebugCharFromID(int id) {
    return hacky_debug_chars[id];
}
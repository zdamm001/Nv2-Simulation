#pragma once
#include <vector>

#include "..\\flash\\utils\\ByteArray.h"
#include "edat.h"

using namespace std;

class Editor_State {
    public:
        vector<unsigned int> tileIDs;
        vector<vector<unsigned int>> entities;
    public:
        Editor_State();
        static Editor_State Load_From_Bytes(ByteArray& bytes);
        static ByteArray Save_To_Bytes(const Editor_State& state);
};
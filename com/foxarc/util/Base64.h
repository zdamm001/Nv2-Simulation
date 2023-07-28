#pragma once
#include <string>
#include <vector>

#include "..\\..\\..\\flash\\utils\\ByteArray.h"

using namespace std;

class Base64 {
    private:
        static const vector<char> encodeChars;
        static const vector<int> decodeChars;
    public:
        static string encode(const ByteArray& data);
        static ByteArray decode(const string& input);
};
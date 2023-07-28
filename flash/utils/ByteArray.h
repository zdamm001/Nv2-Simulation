#pragma once
#include <vector>
#include <zlib.h>

using namespace std;

class ByteArray {
    private:
        vector<unsigned char> data;
    public:
        ByteArray();
        unsigned int length() const;
        unsigned char operator[](unsigned int index) const;
        void writeByte(unsigned char byte);
        void compress();
        void uncompress();
};

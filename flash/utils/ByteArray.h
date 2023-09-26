#pragma once
#include <vector>
#include <zlib.h>
#include <iostream>

using namespace std;

class ByteArray {
    private:
        vector<unsigned char> data;
        unsigned int position;
    public:
        ByteArray();
        unsigned int length() const;
        unsigned char operator[](unsigned int index) const;
        void writeByte(unsigned char byte);
        void compress();
        void uncompress();
        void setPosition(unsigned int newPosition);
        string readUTF();
        void readBytes(ByteArray& bytes);
        void readBytes(ByteArray& bytes, unsigned int offset, unsigned int length);
        bool isEmpty() const; //maybe delete later
        unsigned int bytesAvailable() const;
        unsigned char readUnsignedByte();
        short readShort();
        unsigned int getPosition() const;
        unsigned char readByte();
        void length(unsigned int newLength);
};

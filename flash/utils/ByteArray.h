#pragma once
#include <vector>
#include <zlib.h>
#include <iostream>

using namespace std;

class ByteArray {
    public:
        enum class Endian {BIG_ENDIAN, LITTLE_ENDIAN};
    private:
        unsigned int position;
        vector<unsigned char> data;
        Endian endian;
    public:
        ByteArray();
        unsigned int length() const;
        void length(unsigned int newLength);
        unsigned char operator[](unsigned int index) const;
        unsigned int getPosition() const;
        void setPosition(unsigned int newPosition);
        unsigned int bytesAvailable() const;
        void writeByte(unsigned char byte);
        unsigned char readUnsignedByte();
        signed char readByte();
        signed short readShort();
        unsigned short readUnsignedShort();
        unsigned int readUnsignedInt();
        signed int readInt();
        string readUTF();
        string readUTFBytes(unsigned int length);
        void readBytes(ByteArray& bytes);
        void readBytes(ByteArray& bytes, unsigned int offset, unsigned int length);
        void writeBytes(const ByteArray& bytes);
        void writeBytes(const ByteArray& bytes, unsigned int offset, unsigned int length);
        void compress();
        void uncompress();
};

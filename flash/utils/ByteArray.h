#pragma once
#include <vector>
#include <zlib.h>
#include <iostream>

using namespace std;

class ByteArray {
    public:
        enum class Endian {BIG_ENDIAN, LITTLE_ENDIAN};
    private:
        vector<unsigned char> data;
        unsigned int position;
        Endian endian;
    public:
        ByteArray();
        unsigned int length() const;
        unsigned char operator[](unsigned int index) const;
        void writeByte(unsigned char byte);
        void compress();
        void uncompress();
        void setPosition(unsigned int newPosition);
        string readUTF();
        string readUTFBytes(unsigned int length);
        void readBytes(ByteArray& bytes);
        void readBytes(ByteArray& bytes, unsigned int offset, unsigned int length);
        unsigned int bytesAvailable() const;
        unsigned char readUnsignedByte();
        signed short readShort();
        unsigned short readUnsignedShort();
        unsigned int getPosition() const;
        signed char readByte();
        void length(unsigned int newLength);
        signed int readInt();
        unsigned int readUnsignedInt();
        void writeBytes(const ByteArray& bytes);
        void writeBytes(const ByteArray& bytes, unsigned int offset, unsigned int length);
};

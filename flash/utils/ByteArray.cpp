#include "ByteArray.h"

ByteArray::ByteArray() {};

unsigned int ByteArray::length() const {
    return data.size();
}

unsigned char ByteArray::operator[](unsigned int index) const {
    if (index < data.size()) {
        return data[index];
    } else {
        return 0;
    }
}

void ByteArray::writeByte(unsigned char byte) {
    data.push_back(byte);
}
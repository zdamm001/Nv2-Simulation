#include "ByteArray.h"

ByteArray::ByteArray() : position(0), data(0) {};

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
    if (position >= data.size()) {
        data.push_back(byte);
    } else {
        data[position] = byte;
    }
    position++;
}

void ByteArray::compress() {
    // Compress the data using zlib
    uLongf compressedSize = compressBound(data.size()); // Get the upper bound of the compressed size
    vector<unsigned char> compressedData(compressedSize); // Create a temporary buffer to hold compressed data
    int result = ::compress2(&compressedData[0], &compressedSize, &data[0], data.size(), Z_BEST_COMPRESSION);
    if (result == Z_OK) {
        data.assign(compressedData.begin(), compressedData.begin() + compressedSize); // Resize to actual compressed size
    } else {
        cerr << "Compression Error: " << zError(result) << endl;
        data.clear(); // Clear the data to indicate compression failure
    }
}

void ByteArray::uncompress() {
    // Decompress the data using zlib
    uLongf decompressedSize = data.size() * 50; // Initial guess at decompressed size
    vector<unsigned char> decompressedData(decompressedSize); // Create a temporary buffer to hold decompressed data
    int result = ::uncompress(&decompressedData[0], &decompressedSize, &data[0], data.size());
    while (result == Z_BUF_ERROR) {
        cerr << "Decompression Error: " << zError(result) << endl;
        decompressedSize *= 2;
        decompressedData.resize(decompressedSize);
        result = ::uncompress(&decompressedData[0], &decompressedSize, &data[0], data.size());
    }
    if (result == Z_OK) {
        data.assign(decompressedData.begin(), decompressedData.begin() + decompressedSize); // Resize to actual decompressed size
    } else {
        cerr << "Decompression Error: " << zError(result) << endl;
        data.clear(); // Clear the data to indicate decompression failure
    }
}

void ByteArray::setPosition(unsigned int newPosition) {
    if (newPosition <= data.size()) {
        position = newPosition;
    }
}

string ByteArray::readUTF() {
    unsigned short length = 0;
    if (position + 2 <= data.size()) {
        length = (data[position] << 8) | data[position + 1];
        position += 2;
    } else {
        return "";
    }

    if (position + length <= data.size()) {
        string utfString(data.begin() + position, data.begin() + position + length);
        position += length;
        return utfString;
    } else {
        return "";
    }
}

void ByteArray::readBytes(ByteArray& bytes) {
    readBytes(bytes, 0, 0);
}

void ByteArray::readBytes(ByteArray& bytes, unsigned int offset, unsigned int length) {
    if (length == 0) {
        length = data.size() - position;
    }
    //OFFSET IS WRONG
    if (position + length <= data.size()) {
        for (unsigned int i = 0; i < length; ++i) {
            bytes.writeByte(data[position + i]);
        }
        bytes.setPosition(offset);
        position += length;
    }
}

bool ByteArray::isEmpty() const {
    return data.empty(); //original has no isEmpty just null check
}

unsigned int ByteArray::bytesAvailable() const {
    return data.size() - position;
}

unsigned char ByteArray::readUnsignedByte() {
    if (position < data.size()) {
        unsigned char byteValue = data[position];
        ++position;
        return byteValue;
    } else {
        return 0;
    }
}

short ByteArray::readShort() {
    if (position + 2 <= data.size()) {
        short shortValue = (data[position] << 8) | data[position + 1];
        position += 2;
        return shortValue;
    } else {
        return 0;
    }
}

unsigned int ByteArray::getPosition() const {
    return position;
}

unsigned char ByteArray::readByte() {
    if (position < data.size()) {
        unsigned char byteValue = data[position];
        ++position;
        return byteValue;
    } else {
        return 0;
    }
}

void ByteArray::length(unsigned int newLength) {
    data.resize(newLength);
}

int ByteArray::readInt() {
    if (position + 4 <= data.size()) {
        int intValue = (data[position] << 24) | (data[position + 1] << 16) | (data[position + 2] << 8) | data[position + 3];
        position += 4;
        return intValue;
    } else {
        return 0;
    }
}

void ByteArray::writeBytes(const ByteArray& bytes) {
    setPosition(0);
    for (unsigned int i = 0; i < bytes.length(); ++i) {
        writeByte(bytes[i]);
    }
}

void ByteArray::writeBytes(const ByteArray& bytes, unsigned int offset, unsigned int length) {
    setPosition(offset);
    if (length == 0) length = bytes.length() - offset;
    if (offset + length <= bytes.length()) {
        for (unsigned int i = offset; i < offset + length; ++i) {
            writeByte(bytes[i]);
        }
    }
}
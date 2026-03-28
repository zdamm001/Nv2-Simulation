#include "ByteArray.h"

ByteArray::ByteArray() : position(0), data(0), endian(Endian::BIG_ENDIAN) {}

unsigned int ByteArray::length() const {
    return data.size();
}

void ByteArray::length(unsigned int newLength) {
    data.resize(newLength, 0);
    if (position > data.size()) {
        position = data.size();
    }
}

unsigned char ByteArray::operator[](unsigned int index) const {
    if (index < data.size()) {
        return data[index];
    }
    return 0;
}

unsigned int ByteArray::getPosition() const {
    return position;
}

void ByteArray::setPosition(unsigned int newPosition) {
    position = newPosition;
}

unsigned int ByteArray::bytesAvailable() const {
    if (position >= data.size()) {
        return 0;
    }
    return data.size() - position;
}

void ByteArray::writeByte(unsigned char byte) {
    if (1 > bytesAvailable()) {
        data.resize(position + 1, 0);
    }
    data[position++] = byte;
}

unsigned char ByteArray::readUnsignedByte() {
    if (1 > bytesAvailable()) {
        throw runtime_error("EOFError: not enough bytes available");
    }
    return data[position++];
}

signed char ByteArray::readByte() {
    if (1 > bytesAvailable()) {
        throw runtime_error("EOFError: not enough bytes available");
    }
    return data[position++];
}

signed short ByteArray::readShort() {
    return readUnsignedShort();
}

unsigned short ByteArray::readUnsignedShort() {
    if (2 > bytesAvailable()) {
        throw runtime_error("EOFError: not enough bytes available");
    }

    unsigned short value = 0;
    if (endian == Endian::BIG_ENDIAN) {
        value = (data[position] << 8) | data[position + 1];
    } else {
        value = data[position] | (data[position + 1] << 8);
    }

    position += 2;
    return value;
}

unsigned int ByteArray::readUnsignedInt() {
    if (4 > bytesAvailable()) {
        throw runtime_error("EOFError: not enough bytes available");
    }

    unsigned int value = 0;
    if (endian == Endian::BIG_ENDIAN) {
        value = (data[position] << 24) | (data[position + 1] << 16) | (data[position + 2] << 8) | data[position + 3];
    } else {
        value = data[position] | (data[position + 1] << 8) | (data[position + 2] << 16) | (data[position + 3] << 24);
    }

    position += 4;
    return value;
}

signed int ByteArray::readInt() {
    return readUnsignedInt();
}

string ByteArray::readUTF() {
    unsigned int length = readUnsignedShort();
    return readUTFBytes(length);
}

string ByteArray::readUTFBytes(unsigned int length) {
    if (length > bytesAvailable()) {
        throw runtime_error("EOFError: not enough bytes available");
    }
    string result(data.begin() + position, data.begin() + position + length);
    position += length;
    return result;
}

void ByteArray::readBytes(ByteArray& bytes) {
    readBytes(bytes, 0, 0);
}

void ByteArray::readBytes(ByteArray& bytes, unsigned int offset, unsigned int length) {
    if (length == 0) {
        length = bytesAvailable();
    }

    if (length > bytesAvailable()) {
        throw runtime_error("EOFError: not enough bytes available");
    }

    if (bytes.length() < offset) {
        bytes.length(offset);
    }

    bytes.setPosition(offset);
    for (unsigned int i = 0; i < length; ++i) {
        bytes.writeByte(readUnsignedByte());
    }
}

void ByteArray::writeBytes(const ByteArray& bytes) {
    writeBytes(bytes, 0, 0);
}

void ByteArray::writeBytes(const ByteArray& bytes, unsigned int offset, unsigned int length) {
    const unsigned int sourceLength = bytes.length();

    if (offset >= sourceLength) {
        return;
    }

    const unsigned int maxWritable = sourceLength - offset;

    if (length == 0 || length > maxWritable) {
        length = maxWritable;
    }

    for (unsigned int i = 0; i < length; ++i) {
        writeByte(bytes[offset + i]);
    }
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
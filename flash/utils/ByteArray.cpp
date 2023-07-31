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
#include "Base64.h"

const vector<char> Base64::encodeChars = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

const vector<int> Base64::decodeChars = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1,
    -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, -1, -1, -1, -1, -1
};

string Base64::encode(const ByteArray& data) {
    vector<char> result;
    int byteIndex = 0;
    int length = data.length();
    int paddingBytes = length % 3;
    int bytesInGroupsOfThree = length - paddingBytes;
    while (byteIndex < bytesInGroupsOfThree) {
        int val = (data[byteIndex++] << 16) | (data[byteIndex++] << 8) | data[byteIndex++];
        result.push_back(encodeChars[val >> 18]);
        result.push_back(encodeChars[(val >> 12) & 63]);
        result.push_back(encodeChars[(val >> 6) & 63]);
        result.push_back(encodeChars[val & 63]);
    }
    if (paddingBytes == 1) {
        int val = data[byteIndex++];
        result.push_back(encodeChars[val >> 2]);
        result.push_back(encodeChars[(val & 3) << 4]);
        result.push_back('=');
        result.push_back('=');
    }
    else if (paddingBytes == 2) {
        int val = (data[byteIndex++] << 8) | data[byteIndex++];
        result.push_back(encodeChars[val >> 10]);
        result.push_back(encodeChars[(val >> 4) & 63]);
        result.push_back(encodeChars[(val & 15) << 2]);
        result.push_back('=');
    }
    return string(result.begin(), result.end());
}

ByteArray Base64::decode(const string& input) {
    int byteIndex = 0;
    int length = input.length();
    int paddingBytes = 0;

    while (length > 1 && input[length - 1] == '=') {
        paddingBytes++;
        length--;
    }

    int bytesToProcess = length - paddingBytes;
    ByteArray result;

    while (byteIndex < bytesToProcess) {
        int val = 0;
        int shift = 18;

        // Convert four Base64 characters to three bytes
        for (int i = 0; i < 4; i++) {
            int charValue = decodeChars[input[byteIndex++] & 255];
            if (charValue == -1) {
                throw std::invalid_argument("Invalid Base64 character");
            }
            val |= (charValue & 63) << shift;
            shift -= 6;
        }

        // Write the three bytes to the result ByteArray
        result.writeByte((val >> 16) & 0xFF);
        result.writeByte((val >> 8) & 0xFF);
        result.writeByte(val & 0xFF);
    }

    if (paddingBytes == 1) {
        // Process one padding byte
        int val = 0;
        int shift = 12;
        for (int i = 0; i < 3; i++) {
            int charValue = decodeChars[input[byteIndex++] & 255];
            if (charValue == -1) {
                throw std::invalid_argument("Invalid Base64 character");
            }
            val |= (charValue & 63) << shift;
            shift -= 6;
        }
        result.writeByte((val >> 10) & 0xFF);
        result.writeByte((val >> 2) & 0xFF);
    } else if (paddingBytes == 2) {
        // Process two padding bytes
        int val = 0;
        int shift = 6;
        for (int i = 0; i < 2; i++) {
            int charValue = decodeChars[input[byteIndex++] & 255];
            if (charValue == -1) {
                throw std::invalid_argument("Invalid Base64 character");
            }
            val |= (charValue & 63) << shift;
            shift -= 6;
        }
        result.writeByte((val >> 4) & 0xFF);
    }

    return result;
}

ByteArray Base64::decode(const string& input) {
    int currentIndex = 0;
    int length = input.length();
    ByteArray result;

    loop0:
    while (currentIndex < length) {
        int byte1, byte2, byte3, byte4;

        do {
            byte1 = decodeChars[input[currentIndex++] & 255];
        } while (currentIndex < length && byte1 == -1);

        if (byte1 == -1) {
            break;
        }

        do {
            byte2 = decodeChars[input[currentIndex++] & 255];
        } while (currentIndex < length && byte2 == -1);

        if (byte2 == -1) {
            break;
        }

        result.writeByte((byte1 << 2) | ((byte2 & 48) >> 4));

        while ((byte3 = input[currentIndex++] & 255) != 61) {
            byte3 = decodeChars[byte3];
            if (!(currentIndex < length && byte3 == -1)) {
                if (byte3 == -1) {
                    return result;
                }

                result.writeByte(((byte2 & 15) << 4) | ((byte3 & 60) >> 2));

                while ((byte4 = input[currentIndex++] & 255) != 61) {
                    byte4 = decodeChars[byte4];
                    if (!(currentIndex < length && byte4 == -1)) {
                        if (byte4 == -1) {
                            return result;
                        }

                        result.writeByte(((byte3 & 3) << 6) | byte4);
                        goto loop0;
                    }
                }
                return result;
            }
        }
        return result;
    }
    return result;
}

ByteArray Base64::decode(const string& input) {
    int currentIndex = 0;
    int length = input.length();
    ByteArray result;

    bool continueLoop = true; // Flag to control the loop flow

    while (currentIndex < length && continueLoop) {
        int byte1, byte2, byte3, byte4;

        do {
            byte1 = decodeChars[input[currentIndex++] & 255];
        } while (currentIndex < length && byte1 == -1);

        if (byte1 == -1) {
            break;
        }

        do {
            byte2 = decodeChars[input[currentIndex++] & 255];
        } while (currentIndex < length && byte2 == -1);

        if (byte2 == -1) {
            break;
        }

        result.writeByte((byte1 << 2) | ((byte2 & 48) >> 4));

        while ((byte3 = input[currentIndex++] & 255) != 61) {
            byte3 = decodeChars[byte3];
            if (!(currentIndex < length && byte3 == -1)) {
                if (byte3 == -1) {
                    continueLoop = false; // Set the flag to exit the outer loop
                    break; // Break from the inner loop
                }

                result.writeByte(((byte2 & 15) << 4) | ((byte3 & 60) >> 2));

                while ((byte4 = input[currentIndex++] & 255) != 61) {
                    byte4 = decodeChars[byte4];
                    if (!(currentIndex < length && byte4 == -1)) {
                        if (byte4 == -1) {
                            continueLoop = false; // Set the flag to exit the outer loop
                            break; // Break from the innermost loop
                        }

                        result.writeByte(((byte3 & 3) << 6) | byte4);
                        continueLoop = true; // Set the flag to continue the outer loop
                        break; // Break from the middle loop
                    }
                }

                continueLoop = true; // Set the flag to continue the outer loop
                break; // Break from the middle loop
            }
        }
    }

    return result;
}
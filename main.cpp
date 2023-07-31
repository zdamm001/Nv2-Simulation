#include <iostream>

#include "com\\foxarc\\util\\Base64.h"
#include "flash\\utils\\ByteArray.h"
#include "base64.h"

using namespace std;

int main() {
    ByteArray a;
    a.writeByte('T');
    a.writeByte('E');
    a.writeByte('S');
    a.writeByte('T');
    a.compress();
    string b = Base64::encode(a);
    cout << b << endl;
    ByteArray c = Base64::decode(b);
    c.uncompress();
    cout << a[0] << a[1] << a[2] << a[3] << endl;
    a.uncompress();
    cout << a[0] << a[1] << a[2] << a[3] << endl;
    cout << c[0] << c[1] << c[2] << c[3] << endl;
    string replay = "eNpjYUEHrEzMGBAMgAwWVmoCFnIBAwAJoAL4";
    ByteArray data = Base64::decode(replay);
    for (int i = 0; i < data.length(); ++i) {
        cout << int(data[i]) << ' ';
    }
    cout << endl;
    string decoded2 = base64_decode(replay);
    for (int i = 0; i < data.length(); ++i) {
        cout << int(decoded2[i]) << ' ';
    }
    data.uncompress();
    cout << endl << data.length() << endl;
    for (int i = 0; i < data.length(); ++i) {
        cout << int(data[i]) << ' ';
    }
    cout << endl;
    data.compress();
    cout << Base64::encode(data) << endl;
    data.uncompress();
    cout << endl << data.length() << endl;
    for (int i = 0; i < data.length(); ++i) {
        cout << int(data[i]) << ' ';
    }
    cout << endl;
    cout << replay << endl;
    cout << base64_encode(reinterpret_cast<const unsigned char*>(decoded2.c_str()), decoded2.length()) << endl;
    ByteArray data_ = Base64::decode(replay);
    cout << Base64::encode(data_) << endl;
    string replay2 = "eNpjZGQAAAAIAAM=";
    ByteArray data2 = Base64::decode(replay2);
    data2.uncompress();
    cout << endl << data2.length() << endl;
    for (int i = 0; i < data2.length(); ++i) {
        cout << int(data2[i]) << ' ';
    }
    data2.compress();
    cout << endl << Base64::encode(data2) << endl;
    for (int i = 0; i < 3; ++i) {
        data2.uncompress();
        data2.compress();
        cout << Base64::encode(data2) << endl;
    }
    cout << replay2 << endl;
    ByteArray data3 = Base64::decode(replay2);
    for (int i = 0; i < data3.length(); ++i) {
        cout << int(data3[i]) << ' ';
    }
    cout << endl;
    data3.uncompress();
    data3.compress();
    for (int i = 0; i < data3.length(); ++i) {
        cout << int(data3[i]) << ' ';
    }
    cout << endl;
    cout << replay << endl;
    ByteArray data4 = Base64::decode(replay);
    for (int i = 0; i < data4.length(); ++i) {
        cout << int(data4[i]) << ' ';
    }
    cout << endl;
    data4.uncompress();
    for (int i = 0; i < data4.length(); ++i) {
        cout << int(data4[i]) << ' ';
    }
    cout << endl;
    data4.compress();
    for (int i = 0; i < data4.length(); ++i) {
        cout << int(data4[i]) << ' ';
    }
    cout << endl;
    data4.uncompress();
    for (int i = 0; i < data4.length(); ++i) {
        cout << int(data4[i]) << ' ';
    }
    cout << endl;
    return 0;
}
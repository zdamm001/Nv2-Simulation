#include <iostream>

#include "com\\foxarc\\util\\Base64.h"
#include "flash\\utils\\ByteArray.h"

using namespace std;

int main() {
    string map = "eNpj4AjNK8ksyUlNYQACxpEA+BiggB+rNCdMmgO7djaILDsuWR4QxYtDnoGBG0Rx4QhqUZjdIlilhYCOAkpyMghjlRYEOpkThAUYRzpgYPSyY+D2MjMzs9AxUwnT8FBwsAmyijJz0vHTYeCzsrOyMjOyMrJSslKLsIuwijIK0wtTClPzUPPQAun0UGLAAwDdURQc";
    ByteArray mapData = Base64::decode(map);
    mapData.uncompress();
    for (int i = 0; i < mapData.length(); ++i) {
        cout << int(mapData[i]) << ' ';
    }
    mapData.compress();
    cout << endl << Base64::encode(mapData) << endl;
    return 0;
}
#include <iostream>

#include "com\\foxarc\\util\\Base64.h"
#include "flash\\utils\\ByteArray.h"

using namespace std;

int main() {
    string replay = "eNpjYUEHrEzMGBAMgAwWVmoCFnIBAwAJoAL4";
    ByteArray replayData = Base64::decode(replay);
    replayData.uncompress();
    for (int i = 0; i < replayData.length(); ++i) {
        cout << int(replayData[i]) << ' ';
    }
    replayData.compress();
    cout << endl << Base64::encode(replayData) << endl;
    return 0;
}
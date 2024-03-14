#include <iostream>
#include <fstream>
#include <windows.h>
#include <chrono>
#include <thread>

#include "com\\metanet\\App_MultiPurpose.h"
#include "com\\foxarc\\util\\Base64.h"
#include "com\\metanet\\commands\\StoreDefaults.h"

string holdIt = "00000000000010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010106000000000000000000000000000000000000000000000000070101010101000000000000000000000000000000000000000000000000000001010101010000000000000000000000000000000000000000000000000000010101010100000000000000000000000000000000000000000000000000000101010101000000000004140404040510000000041404040405100000000001010101010101061202021000000003120202020210000000031711000000010101010100000000000000000000000000000000000000000000000000000101010101000000000000000000000000000000000000000000000000000001010101010000000000000000000000000000000000000000000000000000010101010100000000000000000000000000000000000000000000000000000101010101000000000000000000000000000000000414051000000801090001010101010101010109000801010109140811010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010100010216400712284a3642544a6242244a3242504a6e3a5c2e4c204e2c2c2042204c1c2c14342424245c1040204e1040303e282e20021c262a262e26265c245c225c204a204820462c264e26403648464646444640664e564c564001021e2a1e200000000000000102784600000000000000000000000000000000000000000";
// added 4 0's to holdIt (empty title)
string burningChrome = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000801000000010900000000000000000000000000000000000000000008010101010000000101010109000000000000000000000001010100000000010101010100000001010101010000000001010100000000070101000000000000000000000000000000000000000000010106000000000001010000000000000000000000000000000000000000000101000000000000010100000000000000000000000000000000000000000001010000000000000701000000010101000000000000000000010101000000010600000000000000000000000101060000000000000000000701010000000000000000000000000000000001010000000000000000000000010100000000000000000000000000000000010100000000000000000000000101000000000000000000000000000000000106000000000000000000000007010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000101010000000000000000000000000000000000010101000000000000000007010100000000000000000000000000000000000101060000000000000000000101000000000000000000000000000000000001010000000000000000000001010000010900000000000000000008010000010100000000000000000000070100000101010109000000080101010100000106000000000000000000000000000001010101010101010101010101000000000000000000000000000000000000010101010101010101010101010000000000000000000001024650000002026646624000000000000000000000000000000000000000000000000000000000000";
// added 4 0's above
string holdItReplay = "eNpjZQUCFryAgDQOwIQBsKtjwC7FigQYmSEA2TAGFvIAKzMMMLISDZiYsQIm8gGJetGig4ECmxkAyB0GPA==";
string burningChromeReplay = "eNpjYSEAWJHZmICFSoABAJrKAjU=";
string burningChromeReplay2 = "eNpjYSEAWFmRmOiAhfqAAQCvrgJZ";
string burningChromeReplay3 = "eNpjYcEFGKA0KysrC4KJClioDxgArdQCVQ==";
string burningChromeReplay4 = "eNpjYcEFGKA0KxAgMVEACy0AAwCzAQJe";

void Initialize(App_MultiPurpose& app);
void Inject(App_MultiPurpose& app);
enum bruteTypes {allCombosWithoutJump};
enum finishTypes {holdRUntilCanJump, completeUnlessInAir};
enum clocks {N, J, L, LJ, R, RJ, LR, LRJ};
void bruteForce(ByteArray&, ByteArray&, unsigned int, unsigned int, unsigned int, unsigned int, vector<char>);

ofstream fout;

int main() {
    ByteArray levelBytes = sim_globals::StringtoBA(burningChrome);
    ByteArray replayBytes = Base64::decode(burningChromeReplay);
    replayBytes.uncompress();
    fout.open("resultBrute.txt");
    if (!fout.is_open()) {cerr << "Error opening resultBrute.txt"; return 1;}
    bruteForce(levelBytes, replayBytes, 83-4, 18+4, bruteTypes::allCombosWithoutJump, finishTypes::completeUnlessInAir, vector<char>({clocks::R, clocks::R, clocks::R, clocks::R, clocks::R, clocks::R, clocks::R, clocks::R, clocks::J}));
    fout.close();
    return 0;
}

void bruteForce(ByteArray& level, ByteArray& replay, unsigned int startBruteFrame, unsigned int numBruteFrames, unsigned int bruteType, unsigned int finishType, vector<char> endFrames) {
    App_MultiPurpose app;
    Initialize(app);
    Inject(app);
    app.options->resetScoreOnDeath = true;
    app.options->scoreGoldImmediately = true;
    ByteArray replayCopy = replay;//if frames < start + brute add them FIX
    if (bruteType == bruteTypes::allCombosWithoutJump) {
        vector<int> inputTypes = {4, 0, 2};
        vector<char> inputTypesChar = {'R', 'N', 'L'};
        // vector<int> inputTypes = {4, 0};
        // vector<char> inputTypesChar = {'R', 'N'};
        long long int totalCombinations = pow(inputTypes.size(), numBruteFrames);
        if (finishType == finishTypes::holdRUntilCanJump) {
            replayCopy.setPosition(startBruteFrame + numBruteFrames - 1);
            for (int i = 0; i < 100; ++i) {
                replayCopy.writeByte(4);
            }
        }
        else if (finishType == finishTypes::completeUnlessInAir) {
            replayCopy.setPosition(startBruteFrame + numBruteFrames - 1);
            for (int i = 0; i < endFrames.size(); ++i) {
                replayCopy.writeByte(endFrames[i]);
            }
        }
        app.watchPlayerSelectedReplay(&level, &replayCopy);
        for (int j = 0; j < startBruteFrame - 1; ++j) {
            app.tick();
        }
        app.NEW_SaveState();
        fout << "brute_clocks end_frame posx posy velx vely ticks\n";
        for (long long int i = 0; i < totalCombinations; ++i) {
            long long int num = i;
            ByteArray& replaySave = app.NEW_getSaveFrames(0);
            replaySave.setPosition(startBruteFrame - 1);
            string bruteClocks = "";
            int numTypes[3] = {0,0,0};
            for (int j = 0; j < numBruteFrames; ++j) {
                ++numTypes[num % inputTypes.size()];
                //fout << inputTypesChar[num % inputTypes.size()];
                bruteClocks += inputTypesChar[num % inputTypes.size()];
                replaySave.writeByte(inputTypes[num % inputTypes.size()]);
                num /= inputTypes.size();
            }
            if (numTypes[2] > 2 || numTypes[1] > 3 || numTypes[2] + numTypes[1] > 4) continue;
            //if (numTypes[1] > 8) continue;
            app.NEW_watchReplayFromSave();
            for (int j = 0; j < numBruteFrames; ++j) {
                app.tick();
            }
            Ninja* player = app.NEW_getPlayer(0);
            if (finishType == finishTypes::holdRUntilCanJump) {
                for (int j = 0; j < 100; ++j) {
                    app.tick();
                    if (player->NEW_GetInAir() == false) {
                        break;
                    }
                }
            }
            else if (finishType == finishTypes::completeUnlessInAir) {
                for (int j = 0; j < endFrames.size(); ++j) {
                    app.tick();
                    if (player->NEW_GetInAir() == true) {
                        break;
                    }
                }
            }
            if (app.NEW_getFrameNum() != 109) continue;
            //app.exitReplay();
            vec2 pos = player->GetPos();
            vec2 vel = player->GetVel();
            fout << bruteClocks << ' ' << app.NEW_getFrameNum() << ' ' << pos.x << ' ' << pos.y << ' ' << vel.x << ' ' << vel.y << ' ' << app.NEW_getCurrentTicks() << '\n';
        }
    }
}

void Initialize(App_MultiPurpose& app) {
    app.initialize();
    edat::Initialize();
    sim_globals::Initialize();
    Entity_Drone_Base::Initialize();
    Ninja::Initialize();
    edgedefs::Initialize();
    tiledefs::Initialize();
    tiletypes::Initialize();
}

void Inject(App_MultiPurpose& app) {
    app.soloKeys = new PlayerKeys();
    app.coopKeys = new PlayerKeys();
    app.globalKeys = new GlobalKeys();
    app.options = new Options();
    StoreDefaults defaults;
    defaults.soloKeys = app.soloKeys;
    defaults.coopKeys = app.coopKeys;
    defaults.globalKeys = app.globalKeys;
    defaults.options = app.options;
    app.options->coopMode = false;
    defaults.execute();
}
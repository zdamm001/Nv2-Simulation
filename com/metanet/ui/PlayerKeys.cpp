#include "PlayerKeys.h"

PlayerKeys::PlayerKeys() : _playerBindings(NUMBER_OF_PLAYER_KEYS * MAX_NUMBER_OF_PLAYERS) { }

void PlayerKeys::bindActionKeyForPlayer(unsigned int keyType, unsigned int binding, unsigned int playerIndex) {
    _playerBindings[playerIndex * NUMBER_OF_PLAYER_KEYS + keyType] = binding;
}

int PlayerKeys::getActionKeyForPlayer(unsigned int keyType, unsigned int playerIndex) const {
    return _playerBindings[playerIndex * NUMBER_OF_PLAYER_KEYS + keyType];
}

vector<int> PlayerKeys::getActions(const vector<int>& keyTypes) {
    vector<int> actionKeys;
    for (int player = 0; player < MAX_NUMBER_OF_PLAYERS; ++player) {
        for (int i = 0; i < keyTypes.size(); ++i) {
            actionKeys.push_back(getActionKeyForPlayer(keyTypes[i], player));
        }
    }
    return actionKeys;
}

string PlayerKeys::GetKeyConfigString() const {
    ostringstream ssout;
    for (size_t i = 0; i < _playerBindings.size(); ++i) {
        if (i != 0) {
            ssout << ",";
        }
        ssout << _playerBindings[i];
    }
    return ssout.str();
}

void PlayerKeys::SetKeyConfigString(const string& configString) {
    vector<string> splitBindings;
    istringstream ssin(configString);
    string token;
    
    while (getline(ssin, token, ',')) {
        splitBindings.push_back(token);
    }

    for (size_t i = 0; i < splitBindings.size() && i < _playerBindings.size(); ++i) {
        _playerBindings[i] = stoi(splitBindings[i]);
    }
}
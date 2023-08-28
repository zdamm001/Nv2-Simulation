#include "App_MultiPurpose.h"

App_MultiPurpose::App_MultiPurpose() {
    //_timeFormatter = new TimeFormatter();
}

void App_MultiPurpose::initialize() {
    sim_globals::sim_rate = 60;
    _defaultStartingTicks = 90 * sim_globals::sim_rate;
    _startingTicks = _defaultStartingTicks;
    _ticksPerGold = 2 * sim_globals::sim_rate;
    _gameOverCooldown = 0;
    _uiState = MenuStates::MAIN_MENU;
    _gameState = GameStates::UNLOADED;
}

void App_MultiPurpose::prepareSessionFromBytes(ByteArray* levelData, ByteArray* replayData) {
    ByteArray replay;
    int playerCount = 0;

    clearGame();
    _lastLevel = levelData;
    _lastReplay = replayData;

    if (replayData) {
        replay = ByteArray();
        replayData->readBytes(replay, 0, replayData->bytesAvailable());
    }

    _levelName = levelData->readUTF();
    initializeInGameUI();

    ByteArray editorStateData = ByteArray();
    levelData->readBytes(editorStateData);
    levelData->setPosition(0);

    Editor_State loadedEditorState = Editor_State::Load_From_Bytes(editorStateData);

    if (options.coopMode && !_replayChosenByPlayer) {
        playerCount = 2;
        _playerKeys = coopKeys;
    } else {
        playerCount = 1;
        _playerKeys = soloKeys;
    }

    vector<int> playerActions = _playerKeys->getActions({PlayerKeys::JUMP, PlayerKeys::LEFT, PlayerKeys::RIGHT});
    _sim = sim_loader::LoadLevel_EditorState(playerActions, {options.p1Colour, options.p2Colour}, input, replay, playerCount, loadedEditorState);
    initializeEngine();
}
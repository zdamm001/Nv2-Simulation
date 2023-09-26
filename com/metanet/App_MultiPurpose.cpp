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

void App_MultiPurpose::playSingleLevelFromBytes(ByteArray* levelData, string levelID) {
    playLevel(levelData);
    _currentLevel = levelID;
    _startingTicks = _defaultStartingTicks;
    _currentTicks = _startingTicks;
    _ticksElapsed = 0;
    _playingLevelset = false;
}

void App_MultiPurpose::playLevel(ByteArray* levelData) {
    _levelData = levelData;
    _isReplay = false;
    prepareSessionFromBytes(_levelData, nullptr);
    _goldCollected = 0;
    _uiState = MenuStates::PLAYING_GAME;
    _gameState = GameStates::PRE_GAME;
    //_hud = new HUD();
    initializeInGameUI();
    //uiStage.addChild(_hud);
}

void App_MultiPurpose::prepareSessionFromBytes(ByteArray* levelData, ByteArray* replayData) {
    ByteArray replay;
    int playerCount = 0;

    clearGame();
    _lastLevel = levelData;
    _lastReplay = replayData;

    if (replayData) {
        replayData->readBytes(replay, 0, replayData->bytesAvailable());
    }

    _levelName = levelData->readUTF();
    initializeInGameUI();

    ByteArray editorStateData = ByteArray();
    levelData->readBytes(editorStateData);
    levelData->setPosition(0);

    Editor_State loadedEditorState = Editor_State::Load_From_Bytes(editorStateData);

    if (options->coopMode && !_replayChosenByPlayer) {
        playerCount = 2;
        _playerKeys = coopKeys;
    } else {
        playerCount = 1;
        _playerKeys = soloKeys;
    }

    vector<int> playerActions = _playerKeys->getActions({PlayerKeys::JUMP, PlayerKeys::LEFT, PlayerKeys::RIGHT});
    _sim = sim_loader::LoadLevel_EditorState(playerActions, {options->p1Colour, options->p2Colour}, input, replay, playerCount, loadedEditorState);
    initializeEngine();
}

void App_MultiPurpose::initializeEngine() {
    //_gfx = new GraphicsManager(gameStage, _sim.GFX_GetEntityList(), _sim.GFX_GetPlayerList(), _sim.GFX_GetTileIDs(), Simulator::GRID_NUM_ROWS, Simulator::GRID_NUM_COLS, true);
    //_sfx = new SoundManager();
    //_sim->HACKY_SetAV(_gfx,_sfx);
    //_gfx.Render();
    _sim->APP_EnablePlayer(0);
    if (options->coopMode && !_replayChosenByPlayer) {
        _sim->APP_EnablePlayer(1);
    }
}

void App_MultiPurpose::clearGame() {
    _sim = nullptr; //call delete
    //if(_gfx != nullptr) {
    //    _gfx.Clear();
    //    _gfx = nullptr;
    //}
    //_sfx = nullptr;
}

void App_MultiPurpose::initializeInGameUI() {
    //if(!_hud) return;
    //_hud.gold_collected.visible = !options.scoreGoldImmediately;
    //_hud.leveltext.text = _levelName;
}
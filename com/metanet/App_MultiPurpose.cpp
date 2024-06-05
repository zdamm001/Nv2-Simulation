#include "App_MultiPurpose.h"

App_MultiPurpose::App_MultiPurpose() {
    _sim = nullptr;
    _timeFormatter = new TimeFormatter();
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

void App_MultiPurpose::destroy() {
    if (_gameState == GameStates::PAUSED_IN_GAME) {
        //dispatch(InGameEvent(InGameEvent::UNPAUSED));
    }
    if (_playingLevelset && victory() && _currentLevelInSet < _levelSet.size()) {
        instantlyTransferRemainingGoldToTimebar();
        advanceToNextLevel();
        storeGameStats();
    }
    clearGame();
    hideAllGUI();
    setState(MenuStates::MAIN_MENU);
}

void App_MultiPurpose::useLevelSet(vector<ByteArray*> levelSet) {
    _levelSet = levelSet;
}

void App_MultiPurpose::startLevelSet() {
    _currentLevelInSet = 0;
    _startingTicks = _defaultStartingTicks;
    playLevelSet();
}

void App_MultiPurpose::resumeLevelSet(int level, int ticks) {
    _currentLevelInSet = level;
    _startingTicks = ticks;
    playLevelSet();
}

void App_MultiPurpose::playLevelSet() {
    _currentTicks = _startingTicks;
    _ticksElapsed = 0;
    _playingLevelset = true;
    playLevel(_levelSet[_currentLevelInSet]);
    saveProgress();
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

void App_MultiPurpose::showRandomReplay() {
    _isReplay = true;
    _replayChosenByPlayer = false;
    //dispatch(new ReplayEvent(ReplayEvent::RANDOM));
}

void App_MultiPurpose::showNextReplay() {
    _isReplay = true;
    _replayChosenByPlayer = false;
    //dispatch(new ReplayEvent(ReplayEvent::NEXT));
}

void App_MultiPurpose::watchPlayerSelectedReplay(ByteArray* levelData, ByteArray* replayData) {
    _replayChosenByPlayer = true;
    showReplay(levelData, replayData);
}

void App_MultiPurpose::showReplay(ByteArray* levelData, ByteArray* replayData) {
    levelData->setPosition(0);
    replayData->setPosition(0);
    _startingTicks = _defaultStartingTicks;
    _currentTicks = _startingTicks;
    _ticksElapsed = 0;
    _isReplay = true;
    prepareSessionFromBytes(levelData, replayData);
    startReplay();
    _uiState = MenuStates::WATCHING_REPLAY;
    _gameState = GameStates::GAME;
}

void App_MultiPurpose::stopReplay() {
    _gameState = GameStates::UNLOADED;
    clearGame();
    hideAllGUI();
    setState(MenuStates::MAIN_MENU);
}

ByteArray* App_MultiPurpose::getReplay() {
    return _sim->APP_GetReplayBytes()[0];
}

void App_MultiPurpose::tick() {
    //_thisTick = getTimer();
    input.Tick();
    //debugRenderer.Clear();

    switch (_uiState) {
        case MenuStates::PLAYING_GAME:
            tickGame();
            break;
        case MenuStates::GAME_OVER:
            tickGameOver();
            break;
        case MenuStates::WATCHING_REPLAY:
            tickReplay();
            break;
    }

    checkDebugKeys();
    _lastTick = _thisTick;
}

void App_MultiPurpose::checkDebugKeys() {
    // if (input.IsKeyDown(Keyboard::INSERT) || input.CapsLock()) {
    //     debugRenderer.DrawStringAtPosition("ms/f: " + to_string(_thisTick - _lastTick), 1, 530);
    //     if (_performanceGraph) {
    //         _performanceGraph->visible = true;
    //     }
    // } else if (_performanceGraph) {
    //     _performanceGraph->visible = false;
    // }
}

void App_MultiPurpose::prepareSessionFromBytes(ByteArray* levelData, ByteArray* replayData) {
    ByteArray* replay = nullptr;
    int playerCount = 0;

    clearGame();
    _lastLevel = levelData;
    _lastReplay = replayData;

    if (replayData) {
        replay = new ByteArray();
        replayData->readBytes(*replay, 0, replayData->bytesAvailable());
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

void App_MultiPurpose::startReplay() {
    if (_replayChosenByPlayer) {
        //_hud = new HUD();
        //_hud->prompt->visible = false;
        initializeInGameUI();
        //uiStage->addChild(_hud);
    } else {
        hideAllGUI();
    }

    setState(_uiState);
    startGameImmediately();
}

void App_MultiPurpose::initializeEngine() {
    //_gfx = new GraphicsManager(gameStage, _sim->GFX_GetEntityList(), _sim->GFX_GetPlayerList(), _sim->GFX_GetTileIDs(), Simulator::GRID_NUM_ROWS, Simulator::GRID_NUM_COLS, true);
    //_sfx = new SoundManager();
    //_sim->HACKY_SetAV(_gfx,_sfx);
    //_gfx->Render();
    _sim->APP_EnablePlayer(0);
    if (options->coopMode && !_replayChosenByPlayer) {
        _sim->APP_EnablePlayer(1);
    }
}

void App_MultiPurpose::tickGame() {
    switch (_gameState) {
        case GameStates::PRE_GAME:
            tickPreGame();
            break;
        case GameStates::GAME:
            tickGameInProgress();
            break;
        case GameStates::POST_GAME:
            tickPostGame();
            break;
        case GameStates::PAUSED_IN_GAME:
            tickPausedGame();
            break;
    }
}

void App_MultiPurpose::tickGameOver() {
    if (playerReadyToProceed()) {
        exit();
    }
}

void App_MultiPurpose::tickReplay() {
    switch (_gameState) {
        case GameStates::GAME:
            tickReplayInProgress();
            break;
        case GameStates::POST_GAME:
            tickReplayPostGame();
            break;
    }
}

void App_MultiPurpose::tickPreGame() {
    updateInGameDisplay();
    //gfx->Render();
    if (playerReadyToProceed()) {
        startGameImmediately();
    } else if (playerWantsToExit()) {
        exit();
    }
}

void App_MultiPurpose::startGameImmediately() {
    _gameState = GameStates::GAME;
    //_start = getTimer();
    _pausedTime = 0;
}

void App_MultiPurpose::exit() {
    destroy();
    //dispatch(MenuEvent(MenuEvent::SHOW_LAST_SCREEN));
}

void App_MultiPurpose::exitReplay() {
    clearGame();
    hideAllGUI();
    setState(MenuStates::MAIN_MENU);
    //dispatch(MenuEvent(MenuEvent::SHOW_LAST_SCREEN));
}

void App_MultiPurpose::tickGameInProgress() {
    updateInGameDisplay();
    //_hud.prompt.visible = false;
    checkForSuicides();
    if (playerWantsToPause()) {
        _gameState = GameStates::PAUSED_IN_GAME;
        //dispatch(InGameEvent(InGameEvent::PAUSED));
        return;
    }
    tickSimulator();
    if (finished()) {
        triggerGameEnd();
    }
}

void App_MultiPurpose::tickPostGame() {
    updateInGameDisplay();
    tickSimulator();
    _gameOverCooldown = max(0.0, _gameOverCooldown - 1);
    if (_gameOverCooldown > 0) {
        return;
    }
    if (playerReadyToProceed()) {
        showHUD();
        continueGame();
    } else if (playerWantsToExit()) {
        exit();
    }
    if (_goldCollected > 0 && victory()) {
        tickGoldTransferToTimebar();
    }
}

void App_MultiPurpose::tickGoldTransferToTimebar() {
    --_goldCountdown;
    if (_goldCountdown <= 0) {
        transferOneUnitOfGoldToTimebar();
    }
}

void App_MultiPurpose::transferOneUnitOfGoldToTimebar() {
    --_goldCollected;
    _currentTicks += _ticksPerGold;
    _goldCountdown = GOLD_DELAY;
}

void App_MultiPurpose::instantlyTransferRemainingGoldToTimebar() {
    _currentTicks += _goldCollected * _ticksPerGold;
    _goldCollected = 0;
}

void App_MultiPurpose::tickPausedGame() {
    if (input.IsKeyPressed(globalKeys->quit)) {
        //dispatch(InGameEvent(InGameEvent::UNPAUSED));
        exit();
    } else if (input.IsAnyKeyPressed()) {
        //dispatch(InGameEvent(InGameEvent::UNPAUSED));
        _gameState = GameStates::GAME;
    }
    //_pausedTime += getTimer() - _lastTick;
}

void App_MultiPurpose::tickReplayInProgress() {
    if (_replayChosenByPlayer) {
        updateInGameDisplay();
    }
    if (input.IsKeyPressed(globalKeys->back) && _replayChosenByPlayer) {
        exitReplay();
    } else {
        continueReplay();
    }
}

void App_MultiPurpose::tickReplayPostGame() {
    tickSimulator();
    if (_replayChosenByPlayer) {
        tickChosenReplayPostGame();
    } else {
        tickAutoReplayPostGame();
    }
}

void App_MultiPurpose::tickAutoReplayPostGame() {
    _gameOverCooldown = max(0.0, _gameOverCooldown - 1);
    if (!_replayChosenByPlayer && _gameOverCooldown > 0) {
        return;
    }
    endReplay();
}

void App_MultiPurpose::tickChosenReplayPostGame() {
    //if (!_gameOver) {
    //    endReplay();
    //}
    if (playerReadyToProceed()) {
        hideAllGUI();
        showReplay(_lastLevel, _lastReplay);
    } else if (playerWantsToExit()) {
        exit();
    }
}

void App_MultiPurpose::endReplay() {
    if (_replayChosenByPlayer) {
        stats->score = _currentTicks + _ticksPerGold * _goldCollected;
        showGameOver("replay");
    } else {
        showNextReplay();
    }
}

void App_MultiPurpose::continueGame() {
    if (victory()) {
        instantlyTransferRemainingGoldToTimebar();
    }
    if (_playingLevelset) {
        if (victory()) {
            advanceToNextLevel();
        } else if (_currentTicks <= 0) {
            gameOverTimeUp();
        } else {
            if (options->resetScoreOnDeath) {
                _currentTicks = _startingTicks;
                _ticksElapsed = 0;
            }
            _goldCollected = 0;
            prepareSessionFromBytes(_levelData, nullptr);
        }
    } else if (playerReadyToProceed()) {
        _currentTicks = _startingTicks;
        _ticksElapsed = 0;
        prepareSessionFromBytes(_levelData, nullptr);
    } else {
        exit();
    }
    _gameState = GameStates::PRE_GAME;
}

void App_MultiPurpose::advanceToNextLevel() {
    ++_currentLevelInSet;
    _startingTicks = _currentTicks;
    if (_currentLevelInSet >= _levelSet.size()) {
        if (options->selectedEpisode != -1) {
            //dispatch(InGameEvent(InGameEvent::COMPLETE_EPISODE));
            ++options->selectedEpisode;
        }
        showEpisodeVictoryDialog();
    } else {
        if (_playingLevelset) {
            saveProgress();
        }
        _levelData = _levelSet[_currentLevelInSet];
        prepareSessionFromBytes(_levelData, nullptr);
    }
}

void App_MultiPurpose::saveProgress() {
    //sharedObject.setProperty(SavedProperties::SAVED_LEVEL, _currentLevelInSet);
    //sharedObject.setProperty(SavedProperties::SAVED_TICKS_REMAINING, _currentTicks);
    //try {
    //    sharedObject.flush();
    //} catch (const Error& e) {
    //    
    //}
}

void App_MultiPurpose::showEpisodeVictoryDialog() {
    clearSavedProgress();
    showGameOver("episode");
    setState(MenuStates::GAME_OVER);
}

void App_MultiPurpose::clearSavedProgress() {
    //delete sharedObject.data[SavedProperties::SAVED_CHALLENGE];
    //delete sharedObject.data[SavedProperties::SAVED_EPISODE];
    //delete sharedObject.data[SavedProperties::SAVED_LEVEL];
    //delete sharedObject.data[SavedProperties::SAVED_TICKS_REMAINING];
    //try {
    //    sharedObject.flush();
    //} catch (const Error& e) {
    //    
    //}
}

void App_MultiPurpose::gameOverTimeUp() {
    if (_playingLevelset) {
        if (!options->resetScoreOnDeath) {
            clearSavedProgress();
        }
        showGameOver("failure-episode");
    } else {
        showGameOver("failure");
    }
    setState(MenuStates::GAME_OVER);
}

void App_MultiPurpose::continueReplay() {
    tickSimulator();
    if (_sim->APP_IsGameDone()) {
        _gameState = GameStates::POST_GAME;
        _gameOverCooldown = POSTGAME_DELAY;
        _goldCountdown = 0;
    }
}


void App_MultiPurpose::clearGame() {
    delete _sim;
    _sim = nullptr;
    //if(_gfx != nullptr) {
    //    _gfx->Clear();
    //    _gfx = nullptr;
    //}
    //_sfx = nullptr;
}

void App_MultiPurpose::tickSimulator() {
    _sim->Tick(debugRenderer);
    if (!finished()) {
        --_currentTicks;
        ++_ticksElapsed;
        if (_currentTicks <= 0) {
            _currentTicks = 0;
            _sim->APP_Event_TimeUp();
        } else if (options->scoreGoldImmediately) {
            _currentTicks += _sim->APP_GetNumGoldCollectedDuringTick(0) * _ticksPerGold;
            if (options->coopMode && !_isReplay) {
                _currentTicks += _sim->APP_GetNumGoldCollectedDuringTick(1) * _ticksPerGold;
            }
        } else {
            _goldCollected += _sim->APP_GetNumGoldCollectedDuringTick(0);
            if (options->coopMode && !_isReplay) {
                _goldCollected += _sim->APP_GetNumGoldCollectedDuringTick(1);
            }
        }
    }
    //_gfx->Render();
    //_sfx->Tick();
}

void App_MultiPurpose::triggerGameEnd() {
    // unsigned int currTime = getTimer();
    // unsigned int playingTime = currTime - _start - _pausedTime;
    // double playingTicks = playingTime / 17.0;
    // int tickDiff = static_cast<int>(playingTicks) - _ticksElapsed;
    // _gameTooSlow = static_cast<double>(tickDiff) / playingTicks > SLOW_THRESHOLD;
    _gameState = GameStates::POST_GAME;
    _gameOverCooldown = POSTGAME_DELAY;
    //_hud.prompt.visible = true;
    if (_playingLevelset) {
        if (victory()) {
            //_hud.prompt.gotoAndPlay("win");
        } else {
            //_hud.prompt.gotoAndPlay("lose");
        }
    } else {
        storeGameStats();
        showLevelResultDialog();
    }
}

void App_MultiPurpose::storeGameStats() {
    if (_isReplay || !victory()) {
        return;
    }
    stats->score = _currentTicks + _ticksPerGold * _goldCollected;
    stats->isEpisode = _playingLevelset;
    stats->level = _currentLevel;
    checkHighscore();
    if (_currentTicks != _startingTicks) {
        // try {
            stats->replayBytes = _sim->APP_GetReplayBytes()[0];
        // } catch (const Error& in_error) {
        // 
        // }
    }
    if (_isPersonalBest && !options->coopMode && !_playingLevelset && !_gameTooSlow) {
        //dispatch(InGameEvent(InGameEvent::SUBMIT_SCORE));
    }
}

void App_MultiPurpose::showLevelResultDialog() {
    clearSavedProgress();
    if (!victory()) {
        if (_currentTicks > 0) {
            showGameOver("failure-ouch");
        } else {
            showGameOver("failure-time");
        }
    } else if (_isPersonalBest) {
        if (_gameTooSlow) {
            showGameOver("failure-tooslow");
        } else if (_isHighscore) {
            showGameOver("highscore");
        } else {
            showGameOver("personal");
        }
    } else {
        showGameOver("nothing");
    }
}

void App_MultiPurpose::checkHighscore() {
    if (_playingLevelset || options->coopMode) {
        return;
    }
    Level currLevel = options->selectedLevel;
    if (victory()) {
        _isHighscore = _currentTicks > currLevel.minimumHighscore;
        if (_isHighscore) {
            currLevel.minimumHighscore = _currentTicks;
        }
        _isPersonalBest = _currentTicks > currLevel.personalBest;
        if (_isPersonalBest && !options->coopMode && !_playingLevelset && !_gameTooSlow) {
            currLevel.personalBest = _currentTicks;
        }
    } else {
        _isPersonalBest = false;
    }
}

void App_MultiPurpose::setState(int state) {
    _uiState = state;
}

void App_MultiPurpose::showHUD() {
    // if (!_hud) {
        // _hud = new HUD();
        // initializeInGameUI();
        // uiStage.addChild(_hud);
    // }
    // if (_gameOver) {
        // uiStage.removeChild(_gameOver);
        // _gameOver = nullptr;
    // }
}

void App_MultiPurpose::showGameOver(string gameOverMessage) {
    // if (!_gameOver) {
    //     _gameOver = new GameOverPopup();
    //     uiStage.addChild(_gameOver);
    // }
    // if (_hud) {
    //     uiStage.removeChild(_hud);
    //     _hud = nullptr;
    // }
    // _gameOver.gotoAndPlay(gameOverMessage);
    // if (!account.isWeb) {
    //     _gameOver.kong_logo2.visible = false;
    // }
}

void App_MultiPurpose::hideAllGUI() {
    if (_gameState == GameStates::PAUSED_IN_GAME) {
        //dispatch(InGameEvent(InGameEvent::UNPAUSED));
    }
    // if (_gameOver) {
        // uiStage.removeChild(_gameOver);
        // _gameOver = nullptr;
    // }
    // if (_hud) {
        // uiStage.removeChild(_hud);
        // _hud = nullptr;
    // }
}

void App_MultiPurpose::initializeInGameUI() {
    //if(!_hud) return;
    //_hud.gold_collected.visible = !options->scoreGoldImmediately;
    //_hud.leveltext.text = _levelName;
}

void App_MultiPurpose::updateInGameDisplay() {
    updateTimebar();
    updateGoldCounter();
}

void App_MultiPurpose::updateTimebar() {
    //if (!_hud) return;
    double timebarAnimLimit = 360 * sim_globals::sim_rate;
    double timebarPosition = max(0.0, min(1.0, static_cast<double>(_currentTicks) / timebarAnimLimit));
    //int frame = 1 + static_cast<int>(timebarPosition * _hud.timebar.framesLoaded);
    //_hud.timebar.gotoAndStop(frame);
    string formattedTime = _timeFormatter->formatTime(_currentTicks, sim_globals::sim_rate);
    stats->formattedTime = formattedTime.substr(0, formattedTime.length() - 3) + "." + formattedTime.substr(formattedTime.length() - 3);
    //_hud.timetext.timetext0.text = formattedTime[0];
    //_hud.timetext.timetext1.text = formattedTime[1];
    //_hud.timetext.timetext2.text = formattedTime[2];
    //_hud.timetext.timetext3.text = formattedTime[3];
    //_hud.timetext.timetext4.text = formattedTime[4];
    //_hud.timetext.timetext5.text = formattedTime[5];
    //_hud.timetext.timetext6.text = formattedTime[6];
}

void App_MultiPurpose::updateGoldCounter() {
    //if (!_hud) return;
    //_hud.gold_collected.numgold.text = to_string(_goldCollected);
}

void App_MultiPurpose::checkForSuicides() {
    int numPlayers = options->coopMode ? 2 : 1;
    for (int i = 0; i < numPlayers; ++i) {
        checkForPlayerSuicide(i);
    }
}

void App_MultiPurpose::checkForPlayerSuicide(int pID) {
    if (!_sim->APP_IsPlayerDead(pID)) {
        if (input.IsKeyPressed(_playerKeys->getActionKeyForPlayer(PlayerKeys::SUICIDE, pID))) {
            _sim->APP_Event_Suicide(pID);
        }
    }
}

bool App_MultiPurpose::playerReadyToProceed() {
    if (input.IsKeyPressed(_playerKeys->getActionKeyForPlayer(PlayerKeys::JUMP, 0))) {
       return true;
    }
    if (input.IsKeyPressed(Keyboard::SPACE)) {
       return true;
    }
    return false;
}

bool App_MultiPurpose::playerWantsToExit() {
    return input.IsKeyPressed(globalKeys->back);
}

bool App_MultiPurpose::playerWantsToPause() {
    if (input.IsKeyPressed(globalKeys->back)) {
        return true;
    }
    if (input.IsKeyPressed(globalKeys->pause)) {
        return true;
    }
    return false;
}

bool App_MultiPurpose::finished() {
    return _sim->APP_IsGameDone();
}

bool App_MultiPurpose::victory() {
    return _sim->APP_DidPlayerWin();
}

bool App_MultiPurpose::beingPlayed() {
    return !_isReplay || _replayChosenByPlayer;
}

int App_MultiPurpose::gameState() {
    return _gameState;
}

int App_MultiPurpose::uiState() {
    return _uiState;
}

#include <fstream>
#include <sstream>
#include <iomanip>

string App_MultiPurpose::NEW_getDebugString() {
    if (_sim) {
        vec2 pos = _sim->playerList[0]->GetPos();
        vec2 vel = _sim->playerList[0]->GetVel();
        string stateString = Ninja::PSTATE_TO_STRING[_sim->playerList[0]->NEW_GetState()];
        string ninjaInfo = "\nposx: " + NEW_formatNumber(pos.x);
        ninjaInfo += "\nposy: " + NEW_formatNumber(pos.y);
        ninjaInfo += "\nvelx: " + NEW_formatNumber(vel.x);
        ninjaInfo += "\nvely: " + NEW_formatNumber(vel.y);
        ninjaInfo += "\nstate: " + stateString + + " " + to_string(_sim->playerList[0]->rcount) + "R " + to_string(_sim->playerList[0]->lcount) + "L " + to_string(_sim->playerList[0]->jcount) + "J";
        return ninjaInfo;
    }
    return "";
}

string App_MultiPurpose::NEW_getDebugOneLine() {
    if (_sim) {
        vec2 pos = _sim->playerList[0]->GetPos();
        vec2 vel = _sim->playerList[0]->GetVel();
        string state = Ninja::PSTATE_TO_STRING[_sim->playerList[0]->NEW_GetState()];
        string debug = to_string(_sim->NEW_GetFrameNum()) + ": ";
        debug += "px: " + to_string(pos.x) + " py: " + to_string(pos.y);
        debug += " vx: " + to_string(vel.x) + " vy: " + to_string(vel.y);
        debug += " state: " + state + " " + to_string(_sim->playerList[0]->rcount) + "R " + to_string(_sim->playerList[0]->lcount) + "L " + to_string(_sim->playerList[0]->jcount) + "J";
        return debug;
    }
    return "";
}

string App_MultiPurpose::NEW_formatNumber(double value) const {
    ostringstream oss;
    if (value && abs(value) < 1e-6) {
        oss << scientific << setprecision(10) << value;
    } else {
        oss << fixed << setprecision(6) << value;
    }
    return oss.str();
}

unsigned int App_MultiPurpose::NEW_getFrameNum() const {
    if (_sim) {
        return _sim->NEW_GetFrameNum();
    }
    return 0;
}

Ninja* App_MultiPurpose::NEW_getPlayer(unsigned int playerIndex) {
    return this->_sim->playerList[playerIndex];
}

double App_MultiPurpose::NEW_getCurrentTicks() const {
    return this->_currentTicks;
}

// void App_MultiPurpose::NEW_LoadState() {
    // ByteArray savedStateApp; //set pos to 0
    // ByteArray savedLevelData;
    // ByteArray savedStateSim;
    // _levelData = new ByteArray(); //call delete somewhere
    // _levelData->writeBytes(savedLevelData);
    // _currentTicks = savedStateApp.readInt();
    // _ticksElapsed = savedStateApp.readInt();
    // _currentLevel = to_string(savedStateApp.readInt()); // use .toString() in AS3
    // _sim->loadState(savedStateSim);
// }
// 
// void App_MultiPurpose::NEW_SaveState() {
    // ByteArray savedStateApp; //clear these
    // ByteArray savedLevelData;
    // ByteArray savedStateSim;
    // savedLevelData.clear();
    // savedLevelData.writeBytes(*_levelData);
    // savedStateApp.writeInt(_currentTicks);
    // savedStateApp.writeInt(_ticksElapsed);
    // savedStateApp.writeInt(stoi(_currentLevel)); // use parseInt in AS3
    // //since saving _levelName seems complicated, will do levelData->readUTF() later instead;
    // savedStateSim = _sim->saveState(); // check null
// }

// void App_MultiPurpose::NEW_LoadState() {
//     _currentTicks = appState.currentTicks;
//     _ticksElapsed = appState.ticksElapsed;
//     _currentLevel = appState.currentLevel;
//     _levelName = appState.levelName;
//     _sim = sim_loader::LoadFromSavedState(appState);
// }

void App_MultiPurpose::NEW_SaveState() {
    appState.ninjaState.clear();
    appState.entityState.clear();
    appState.currentTicks = _currentTicks;
    appState.ticksElapsed = _ticksElapsed;
    appState.currentLevel = _currentLevel;
    appState.levelName = _levelName;
    appState.isCoopMode = options->coopMode;
    appState.isReplay = _isReplay;
    _sim->saveState(appState);
}

void App_MultiPurpose::NEW_playLevelFromSave() {
    _levelData = nullptr;
    _isReplay = false;
    NEW_prepareSessionFromSave();
    _goldCollected = 0;
    _uiState = MenuStates::PLAYING_GAME;
    _gameState = GameStates::PRE_GAME;
    //_hud = new HUD();
    initializeInGameUI();
    //uiStage.addChild(_hud);
    _currentLevel = appState.currentLevel;
    //_startingTicks = _defaultStartingTicks;
    _currentTicks = appState.currentTicks;
    _ticksElapsed = appState.ticksElapsed;
    _playingLevelset = false;
}

void App_MultiPurpose::NEW_watchReplayFromSave() {
    _replayChosenByPlayer = true;
    //_startingTicks = _defaultStartingTicks;
    _currentTicks = appState.currentTicks;
    _ticksElapsed = appState.ticksElapsed;
    _isReplay = true;
    NEW_prepareSessionFromSave();
    startReplay();
    _uiState = MenuStates::WATCHING_REPLAY;
    _gameState = GameStates::GAME;
}

void App_MultiPurpose::NEW_prepareSessionFromSave() {
    clearGame();
    _lastLevel = nullptr;
    _lastReplay = nullptr;

    _levelName = appState.levelName;
    initializeInGameUI();

    if (appState.isCoopMode && !appState.isReplay) {
        _playerKeys = coopKeys;
    } else {
        _playerKeys = soloKeys;
    }

    _sim = sim_loader::LoadFromSave(appState, _playerKeys->getActions({PlayerKeys::JUMP, PlayerKeys::LEFT, PlayerKeys::RIGHT}), {options->p1Colour, options->p2Colour}, input);

    //_gfx = new GraphicsManager(gameStage, _sim->GFX_GetEntityList(), _sim->GFX_GetPlayerList(), _sim->GFX_GetTileIDs(), Simulator::GRID_NUM_ROWS, Simulator::GRID_NUM_COLS, true);
    //_sfx = new SoundManager();
    //_sim->HACKY_SetAV(_gfx,_sfx);
    //_gfx->Render();
}

ByteArray& App_MultiPurpose::NEW_getSaveFrames(unsigned int playerIndex) {
    return appState.ninjaState[playerIndex].frames;
}

Simulator* App_MultiPurpose::NEW_getSim() const {
    return _sim;
}
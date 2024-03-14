#pragma once
#include <vector>

// #include "..\\..\\audiovisual\\GraphicsManager.h"
// #include "audiovisual\\SoundManager.h"
#include "data\\AccountDetails.h"
// #include "data\\AttractMode.h"
// #include "data\\EpisodeData.h"
// #include "data\\GameStats.h"
#include "data\\Level.h"
#include "data\\Options.h"
// #include "events\\InGameEvent.h"
// #include "events\\MenuEvent.h"
// #include "events\\ReplayEvent.h"
#include "global\\GameStates.h"
#include "global\\MenuStates.h"
// #include "global\\SavedProperties.h"
#include "ui\\GlobalKeys.h"
#include "ui\\PlayerKeys.h"
#include "ui\\TimeFormatter.h"
#include "..\\..\editor\\Editor_State.h"
// #include "..\\..\\flash\\display\\Bitmap.h"
// #include "..\\..\\flash\\display\\Sprite.h"
// #include "..\\..\\flash\\net\\SharedObject.h"
#include "..\\..\\flash\\ui\\Keyboard.h"
#include "..\\..\\flash\\utils\\ByteArray.h"
// #include "..\\..\\flash\\utils\\getTimer.h"
// #include "..\\..\\org\\robotlegs\\mvcs\\Actor.h"
#include "..\\..\\simpleFramework\\SimpleInput.h"
#include "..\\..\\simpleFramework\\SimpleRenderer.h"
#include "..\\..\\simulation\\Simulator.h"
#include "..\\..\\simulation\\sim_globals.h"
#include "..\\..\\simulation\\sim_loader.h"
#include "..\\..\\simulation\\save\\saveState.h"

using namespace std;

class Actor {};
class App {};

class App_MultiPurpose : public Actor, public App {
    private:
        static const int POSTGAME_DELAY = 30;
    public:
        // AttractMode* attractMode;
        SimpleInput input;
        GlobalKeys* globalKeys;
        SimpleRenderer* debugRenderer;
        Options* options;
        // EpisodeData* episodeData;
        // GameStats* stats;
        // SharedObject* sharedObject;
        PlayerKeys* coopKeys;
        PlayerKeys* soloKeys;
        // Sprite* gameStage;
        // Sprite* uiStage;
        AccountDetails* account;
    private:
        TimeFormatter* _timeFormatter;
        Simulator* _sim;
        // GraphicsManager* _gfx;
        // SoundManager* _sfx;
        PlayerKeys* _playerKeys;
        // Bitmap* _performanceGraph;
        // HUD* _hud;
        // GameOverPopup* _gameOver;
        int _uiState = -1;
        int _gameState;
        bool _isHighscore;
        bool _isPersonalBest;
        vector<ByteArray*> _levelSet;
        int _currentLevelInSet;
        int _startingTicks;
        int _defaultStartingTicks;
        int _currentTicks;
        int _ticksElapsed;
        string _currentLevel;
        bool _playingLevelset;
        ByteArray* _levelData;
        bool _replayChosenByPlayer = false;
        string _levelName;
        int _ticksPerGold;
        int _thisTick;
        int _lastTick;
        int _goldCollected;
        int GOLD_DELAY = 8;
        int _goldCountdown;
        bool _isReplay;
        int _start;
        bool _gameTooSlow;
        int _pausedTime;
        double SLOW_THRESHOLD = 0.15;
        double _gameOverCooldown;
        ByteArray* _lastLevel;
        ByteArray* _lastReplay;
        appSave appState;
    public:
        App_MultiPurpose();
        void initialize();
        void destroy();
        void useLevelSet(vector<ByteArray*> levelSet);
        void startLevelSet();
        void resumeLevelSet(int currLevel, int startingTicks);
    private:
        void playLevelSet();
    public:
        void playSingleLevelFromBytes(ByteArray* levelData, string levelID);
    private:
        void playLevel(ByteArray* levelData);
    public:
        void showRandomReplay();
        void showNextReplay();
        void watchPlayerSelectedReplay(ByteArray* levelData, ByteArray* replayData);
        void showReplay(ByteArray* levelData, ByteArray* replayData);
        void stopReplay();
        ByteArray* getReplay();
        void tick();
    private:
        void checkDebugKeys();
        void prepareSessionFromBytes(ByteArray* levelData, ByteArray* replayData);
        void startReplay();
        void initializeEngine();
        void tickGame();
        void tickGameOver();
        void tickReplay();
        void tickPreGame();
        void startGameImmediately();
        void exit();
        void exitReplay();
        void tickGameInProgress();
        void tickPostGame();
        void tickGoldTransferToTimebar();
        void transferOneUnitOfGoldToTimebar();
        void instantlyTransferRemainingGoldToTimebar();
        void tickPausedGame();
        void tickReplayInProgress();
        void tickReplayPostGame();
        void tickAutoReplayPostGame();
        void tickChosenReplayPostGame();
        void endReplay();
        void continueGame();
        void advanceToNextLevel();
        void saveProgress();
        void showEpisodeVictoryDialog();
        void clearSavedProgress();
        void gameOverTimeUp();
        void continueReplay();
        void clearGame();
        void tickSimulator();
        void triggerGameEnd();
        void storeGameStats();
        void showLevelResultDialog();
        void checkHighscore();
        void setState(int uiState);
        void showHUD();
        void showGameOver(string gameOverMessage);
        void hideAllGUI();
        void initializeInGameUI();
        void updateInGameDisplay();
        void updateTimebar();
        void updateGoldCounter();
        void checkForSuicides();
        void checkForPlayerSuicide(int pID);
        bool playerReadyToProceed();
        bool playerWantsToExit();
        bool playerWantsToPause();
        bool finished();
        bool victory();
    public:
        bool beingPlayed();
        int gameState();
        int uiState();
        string NEW_getDebugString();
        string NEW_getDebugOneLine();
        string NEW_formatNumber(double value) const;
        unsigned int NEW_getFrameNum() const;
        Ninja* NEW_getPlayer(unsigned int pID);
        double NEW_getCurrentTicks() const;
        void NEW_SaveState();
        void NEW_playLevelFromSave();
        void NEW_watchReplayFromSave();
        void NEW_prepareSessionFromSave();
        ByteArray& NEW_getSaveFrames(unsigned int playerIndex);
};

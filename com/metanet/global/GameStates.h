#pragma once

class GameStates {
    public:
        static const int UNLOADED = 0;
        static const int PRE_GAME = 1;
        static const int GAME = 2;
        static const int POST_GAME = 3;
        static const int PAUSED_IN_GAME = 4;
        GameStates() = delete;
};
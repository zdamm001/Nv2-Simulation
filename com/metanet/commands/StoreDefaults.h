#pragma once

#include "..\\data\\AccountDetails.h"
#include "..\\data\\Options.h"
#include "..\\global\\Flavours.h"
#include "..\\ui\\GlobalKeys.h"
#include "..\\ui\\PlayerKeys.h"
#include "..\\..\\..\\flash\\ui\\Keyboard.h"
//extends Command

class StoreDefaults {
    public:
        PlayerKeys* coopKeys;
        PlayerKeys* soloKeys;
        GlobalKeys* globalKeys;
        Options* options;
        AccountDetails* account;
    public:
        StoreDefaults();
        void execute();
    private:
        void defaultPlayerKeys();
        void defaultMenuKeys();
        void defaultOptions();
};

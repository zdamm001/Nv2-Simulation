#include "StoreDefaults.h"

StoreDefaults::StoreDefaults() {};

void StoreDefaults::execute() {
    defaultPlayerKeys();
    defaultMenuKeys();
    defaultOptions();
}

void StoreDefaults::defaultPlayerKeys() {
    soloKeys->bindActionKeyForPlayer(PlayerKeys::JUMP, Keyboard::Z, 0);
    soloKeys->bindActionKeyForPlayer(PlayerKeys::LEFT, Keyboard::LEFT, 0);
    soloKeys->bindActionKeyForPlayer(PlayerKeys::RIGHT, Keyboard::RIGHT, 0);
    soloKeys->bindActionKeyForPlayer(PlayerKeys::SUICIDE, Keyboard::K, 0);
    coopKeys->bindActionKeyForPlayer(PlayerKeys::JUMP, Keyboard::SHIFT, 0);
    coopKeys->bindActionKeyForPlayer(PlayerKeys::LEFT, Keyboard::A, 0);
    coopKeys->bindActionKeyForPlayer(PlayerKeys::RIGHT, Keyboard::D, 0);
    coopKeys->bindActionKeyForPlayer(PlayerKeys::SUICIDE, Keyboard::T, 0);
    coopKeys->bindActionKeyForPlayer(PlayerKeys::JUMP, Keyboard::N, 1);
    coopKeys->bindActionKeyForPlayer(PlayerKeys::LEFT, 188, 1);
    coopKeys->bindActionKeyForPlayer(PlayerKeys::RIGHT, 190, 1);
    coopKeys->bindActionKeyForPlayer(PlayerKeys::SUICIDE, Keyboard::O, 1);
}

void StoreDefaults::defaultMenuKeys() {
    globalKeys->up = Keyboard::UP;
    globalKeys->down = Keyboard::DOWN;
    globalKeys->left = Keyboard::LEFT;
    globalKeys->right = Keyboard::RIGHT;

    if (account->isKiosk) {
        globalKeys->pause = Keyboard::ESCAPE;
        globalKeys->quit = Keyboard::ESCAPE;
    } else {
        globalKeys->pause = Keyboard::P;
        globalKeys->quit = Keyboard::Q;
    }

    globalKeys->select = Keyboard::Z;
}

void StoreDefaults::defaultOptions() {
    options->volume = 0.3;
    //SoundMixer.soundTransform = new SoundTransform(this.options->volume);
    options->ninjaFlavour = 0;
    options->p1Colour = Flavours::getP1Flavour(0);
    options->p2Colour = Flavours::getP2Flavour(0);
}
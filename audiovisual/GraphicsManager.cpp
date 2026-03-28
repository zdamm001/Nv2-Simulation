#include "GraphicsManager.h"

GraphicsManager::GraphicsManager(Sprite* gameStage, vector<Entity_Base*>& entities, vector<Ninja*>& players, vector<int>& tileIDs, int rows, int cols, bool enableParticles) {
    num_rows = rows;
    num_cols = cols;
    root = new Sprite();
    gameStage->addChild(root);
    entity_gfxList.resize(entities.size());
    player_gfxList.resize(players.size());
    tile_mcList.resize(num_rows * num_cols);
    vector<DisplayObject*> graphics, ninjaGraphics;

    if (enableParticles) {
        particle_buffer_back = new Sprite();
        graphics.push_back(particle_buffer_back);
    }

    int entityIndex = 0;
    for (Entity_Base* entity : entities) {
        EntityGraphics* graphic = entity->GenerateGraphicComponent();
        if (graphic != nullptr) {
            graphic->RegisterGraphics(graphics);
            entity_gfxList[entityIndex++] = graphic;
        }
    }

    int playerIndex = 0;
    for (Ninja* ninja : players) {
        EntityGraphics_Ninja* graphic = ninja->GenerateGraphicComponent();
        if (graphic != nullptr) {
            graphic->RegisterGraphics(ninjaGraphics);
            player_gfxList[playerIndex++] = graphic;
        }
    }

    for (int i = ninjaGraphics.size() - 1; i >= 0; --i) {
        graphics.push_back(ninjaGraphics[i]);
    }

    if (enableParticles) {
        particle_buffer_front = new Sprite();
        graphics.push_back(particle_buffer_front);
    }

    int tileIndex = 0;
    for (int col = 0; col < num_cols; ++col) {
        for (int row = 0; row < num_rows; ++row) {
            MovieClip* tile = new MovieClip(); //new asset_gfx_tiles()
            tile->x = col * 24 + 12;
            tile->y = row * 24 + 12;
            int index = col + row * num_cols;
            tile->gotoAndStop(tileIDs[index] + 1);
            tile->cacheAsBitmap = true;
            tile_mcList[index] = tile;
            graphics.push_back(tile);
        }
    }

    for (size_t i = 0; i < graphics.size(); ++i) {
        root->addChild(graphics[i]);
    }

    if (enableParticles) {
        pman = new ParticleManager_Classic(particle_buffer_back, particle_buffer_front);
    } else {
        pman = new ParticleManager_Null();
    }
}

GraphicsManager::~GraphicsManager() {
    for (EntityGraphics* entity : entity_gfxList) {
        delete entity;
    }
    for (EntityGraphics_Ninja* ninja : player_gfxList) {
        delete ninja;
    }
    for (MovieClip* tile : tile_mcList) {
        delete tile;
    }
    delete particle_buffer_back;
    delete particle_buffer_front;
    delete pman;
}

void GraphicsManager::Hide() {
    root->visible = false;
}

void GraphicsManager::Show() {
    root->visible = true;
}

void GraphicsManager::Clear() {
    if (root->parent != nullptr) {
        root->parent->removeChild(root);
    }
    SoundMixer::stopAll();
}

ParticleManager* GraphicsManager::GetParticleManager() {
    return pman;
}

void GraphicsManager::Render() {
    for (EntityGraphics* entityGraphics : entity_gfxList) {
        entityGraphics->UpdateState();
    }
    for (EntityGraphics_Ninja* playerGraphics : player_gfxList) {
        playerGraphics->UpdateState();
    }
}
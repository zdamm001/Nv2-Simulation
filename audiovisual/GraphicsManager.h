#pragma once
#include <vector>

#include "entitygraphics\\EntityGraphics.h"
#include "entitygraphics\\EntityGraphics_Ninja.h"
//#include "flash\\display\\DisplayObject.h"
//#include "flash\\display\\MovieClip.h"
//#include "flash\\display\\Sprite.h"
//#include "flash\\media\\SoundMixer.h"
#include "..\\simulation\\entities\\Entity_Base.h"
#include "..\\simulation\\ninja\\Ninja.h"

using namespace std;

class GraphicsManager {
    private:
        Sprite* root;
        vector<EntityGraphics*> entity_gfxList;
        vector<EntityGraphics_Ninja*> player_gfxList;
        vector<MovieClip*> tile_mcList;
        int num_rows;
        int num_cols;
        Sprite* particle_buffer_front;
        Sprite* particle_buffer_back;
        ParticleManager* pman;
    public:
        GraphicsManager(Sprite* gameStage, vector<Entity_Base*>& entities, vector<Ninja*>& players, vector<int>& tileIDs, int rows, int cols, bool enableParticles);
        ~GraphicsManager();
        void Hide();
        void Show();
        void Clear();
        ParticleManager* GetParticleManager();
        void Render();
};
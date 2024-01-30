#pragma once

#include "Entity_Drone_Shooter_Base.h"
//#include "..\\audiovisual\\entitygraphics\\EntityGraphics_Drone_Chaingun.h"
#include "..\\..\\math\\mathutils.h"
#include "..\\..\\math\\vec2.h"
//#include "..\\simpleFramework\\SimpleRenderer.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\colutils.h"
#include "..\\sim_globals.h"

class EntityGraphics_Drone_Chaingun;

class Entity_Drone_Chaingun : public Entity_Drone_Shooter_Base {
    private:
        static inline const int chaingun_maxbullets = 6;
        static inline const double chaingun_spread = 0.3;
        double chaingun_rate;
        int chaingun_count;
        int chaingun_timer;
        vec2 chaingun_dir;
        vec2 chaingun_sweep;
        int chaingun_HACKY_hitmode;
        vec2 chaingun_hit_pos;
        vec2 chaingun_hit_n;
    public:
        Entity_Drone_Chaingun(Grid_Entity& entities, double x, double y, unsigned int facingDir, unsigned int moveType);
        Entity_Drone_Chaingun(Grid_Entity& entities, entitySave& entity);
    protected:
        void Start_Prefiring(Simulator* sim, const vec2& ninjaPos) override;
        void Update_Prefiring(Simulator* sim, const vec2& ninjaPos) override;
        void Start_Firing(Simulator* sim, const vec2& ninjaPos, const vec2& ninjaVel) override;
        bool Update_Firing(Simulator* sim) override;
        void Start_Postfiring(Simulator* sim) override;
    public:
        EntityGraphics* GenerateGraphicComponent() override;
        void GFX_UpdateState(EntityGraphics* graphic);
        void Debug_Draw(SimpleRenderer& rend);
        void saveState(entitySave& state) override;
};

#pragma once

#include "Entity_Drone_Shooter_Base.h"
//#include "..\\audiovisual\\entitygraphics\\EntityGraphics_Drone_Laser.h"
#include "..\\..\\math\\vec2.h"
//#include "..\\simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\colutils.h"
#include "..\\sim_globals.h"
class EntityGraphics_Drone_Laser;

class Entity_Drone_Laser : public Entity_Drone_Shooter_Base {
    private:
        int laser_duration;
        int laser_timer;
        vec2 laser_dir;
        vec2 laser_hit_pos;
        vec2 laser_hit_n;
    public:
        Entity_Drone_Laser(Grid_Entity& entities, double x, double y, unsigned int facingDir, unsigned int moveType);
    protected:
        void Start_Prefiring(Simulator* sim, const vec2& ninjaPos) override;
        void Update_Prefiring(Simulator* sim, const vec2& ninjaPos) override;
        void Start_Firing(Simulator* sim, const vec2& ninjaPos, const vec2& ninjaVel) override;
        bool Update_Firing(Simulator* sim) override;
        void Start_Postfiring(Simulator* sim) override;
        EntityGraphics* GenerateGraphicComponent() override;
        void GFX_UpdateState(EntityGraphics_Drone_Laser* graphics);
        void Debug_Draw(SimpleRenderer& rend) override;
};

#pragma once

#include "..\\..\\math\\vec2.h"
//#include "simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\Segment.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"
#include "..\\sim_globals.h"
#include "entity_helpers.h"

class EntityGraphics;
class EntityGraphics_Rocket;

class Entity_Rocket : public Entity_Base {
    private:
        static const int STATE_IDLE = 0;
        static const int STATE_PREFIRE = 1;    
        static const int STATE_HOMING = 2;
        double maxspeed;
        double accel_start;
        double accel_rate;
        double turn_rate;
        double prefire_delay;
        double prediction_scale;
        int gfx_PREV_STATE;
        vec2 pos;
        vec2 rocket_pos;
        vec2 rocket_dir;
        double rocket_speed;
        double rocket_accel;
        double shot_timer;
        int CUR_STATE;
        int targetIndex;
        vector<Segment*> nearSegs;
        vec2 old_pos;
        vec2 rocket_vel;
        vec2 hit_pos;
        vec2 hit_n;
    public:
        Entity_Rocket(Grid_Entity& entities, double x, double y);
        Entity_Rocket(Grid_Entity& entities, entitySave& entity);
        bool CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) override;
        void Think(Simulator* sim) override;
    private:
        void Event_Explode(Simulator* sim);
    public:
        EntityGraphics* GenerateGraphicComponent() override;
        void GFX_UpdateState(EntityGraphics_Rocket* graphic);
        void Debug_Draw(SimpleRenderer& rend) override;
        // ByteArray saveState() override;
        void saveState(entitySave& state) override;
};
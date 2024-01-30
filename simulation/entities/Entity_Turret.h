#pragma once

#include "..\\..\\math\\vec2.h"
//#include "simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"
#include "..\\sim_globals.h"
#include "entity_helpers.h"

class EntityGraphics;
class EntityGraphics_Turret;

class Entity_Turret : public Entity_Base {
    private:
        static const int STATE_IDLE = 0;
        static const int STATE_TARGETING = 1;
        static const int STATE_PREFIRE = 2;
        static const int STATE_POSTFIRE = 3;
        vector<double> threshold2;
        vector<double> aimspeed;
        vector<double> timerstep;
        double prediction_scale;
        vec2 pos;
        vec2 aim_pos;
        int aim_region;
        double shot_timer;
        int CUR_STATE;
        int targetIndex;
        bool gfx_triggerEvent;
        int HACKY_drawtimer;
        vec2 HACKY_hit_pos;
        vec2 HACKY_hit_n;
        double timer_firetime;
        double prefire_delay;
        double postfire_delay;
        vec2 TEMP_hit_pos;
        vec2 TEMP_hit_n;
    public:
        Entity_Turret(Grid_Entity& entities, double x, double y);
        Entity_Turret(Grid_Entity& entities, entitySave& entity);
        void Think(Simulator* sim) override;
    private:
        void Event_StartIdling();
        void Event_StartTargetting(int ninjaID);
        void Event_ResumeTargetting();
        void Event_StartFiring();
        void Event_StopFiring();
        bool IsCurrentTargetVisible(Simulator* sim, vec2& hitPos, vec2& hitNormal);
        void UpdateAim(const vec2& ninjaPos, const vec2& ninjaVel);
        EntityGraphics* GenerateGraphicComponent();
        void GFX_UpdateState(EntityGraphics_Turret* graphic);
        void Debug_Draw(SimpleRenderer& rend);
        // ByteArray saveState() override;
        void saveState(entitySave& state) override;
};

#pragma once

#include "Entity_Base.h"
#include "..\\..\\math\\mathutils.h"
#include "..\\..\\math\\vec2.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Edges.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\Grid_Segment.h"
#include "..\\ninja\\Ninja.h"

class Entity_Drone_Base : public Entity_Base {
    protected:
        static const unsigned int DIR_R = 0;
        static const unsigned int DIR_D = 1;
        static const unsigned int DIR_L = 2;
        static const unsigned int DIR_U = 3;
        static vector<vec2> DIR_TO_VEC2;
        static vector<double> DIR_TO_RAD;
        static const unsigned int ROT_0 = 0;
        static const unsigned int ROT_90 = 1;
        static const unsigned int ROT_180 = 2;
        static const unsigned int ROT_270 = 3;
        static const unsigned int MOVETYPE_SURFACE_CW = 0;
        static const unsigned int MOVETYPE_SURFACE_CCW = 1;
        static const unsigned int MOVETYPE_WANDER_CW = 2;
        static const unsigned int MOVETYPE_WANDER_CCW = 3;
        static vector<vector<unsigned int>> MOVELIST;
        vec2 pos;
        double speed;
        double r;
        double gfxorn;
    private:
        double step_size;
    protected:
        vec2 next_goal;
        unsigned int facing_DIR;
        unsigned int move_TYPE;
    public:
        Entity_Drone_Base(Grid_Entity& entities, double x, double y, double speed, unsigned int facingDir, unsigned int moveType);
        Entity_Drone_Base(Grid_Entity& entities, entitySave& entity, double speed);
        static void Initialize();
        void Move(Simulator* sim) override;
    private:
        void Move_Forward(Grid_Edges& edges, Grid_Segment& segs, Grid_Entity& entities, const vector<Ninja*>& players);
    protected:
        virtual bool ChooseNextDirAndGoal(Grid_Edges& edges, const vector<Ninja*>& ninjas);
        bool ChooseNextDirAndGoal_HELPER_TestDir(Grid_Edges& edges, unsigned int direction, vec2& nextGoal);
    public:
        void Debug_Draw(SimpleRenderer& rend) override;
        void saveState(entitySave& state) override;
};

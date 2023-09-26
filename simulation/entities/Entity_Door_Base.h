#pragma once

#include "Entity_Base.h"
#include "..\\..\\math\\vec2.h"
//#include "..\\simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\AABB.h"
#include "..\\collision\\Grid_Edges.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\Grid_Segment.h"
#include "..\\collision\\Segment.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"

class Entity_Door_Base : public Entity_Base {
    protected:
        vec2 trigger_pos;
    private:
        double trigger_r;
        Grid_Segment& seg_grid;
    protected:
        Segment* seg;
    private:
        int seg_index;
        Grid_Edges& edge_grid;
        vector<int> edge_indices;
        bool isHorizontal;
        bool isOpen;
    public:
        Entity_Door_Base(Grid_Entity& entities, Grid_Segment& segments, int segmentIndex, Segment* segment, Grid_Edges& edges, std::vector<int>& edgeIndices, bool isHorizontal, double openOffset, double closeOffset, double doorSize, bool isOpen);
        bool CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) override;
    protected:
        virtual void OnCollision(Simulator* sim);
        bool IsDoorOpen();
        void ChangeDoorState(bool state);
    private:
        void RemoveDoorFromWorld();
        void AddDoorToWorld();
    protected:
        vec2 GetDoorPos();
        double GetDoorOrn();
    public:
        void Debug_Draw_Base(SimpleRenderer& renderer, bool drawTrigger);
};


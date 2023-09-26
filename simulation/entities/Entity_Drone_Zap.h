#pragma once

#include "Entity_Drone_Base.h"
//#include "..\\audiovisual\\entitygraphics\\EntityGraphics_Drone_Zap.h"
#include "..\\..\\math\\vec2.h"
//#include "simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"
#include "..\\sim_globals.h"
class EntityGraphics_Drone_Zap;

class Entity_Drone_Zap : public Entity_Drone_Base {
    public:
    Entity_Drone_Zap(Grid_Entity& entities, double x, double y, unsigned int facingDir, unsigned int moveType);
    bool CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) override;
    EntityGraphics* GenerateGraphicComponent() override;
    void GFX_UpdateState(EntityGraphics_Drone_Zap* graphic);
    void Debug_Draw(SimpleRenderer& rend) override;
};

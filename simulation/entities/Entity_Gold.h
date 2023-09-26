#pragma once

#include "Entity_Base.h"
//#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Gold.h"
#include "..\\..\\math\\vec2.h"
//#include "simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"
class EntityGraphics_Gold;

class Entity_Gold : public Entity_Base {
    private:
        vec2 pos;
        double r;
        bool isCollected;
    public:
        Entity_Gold(Grid_Entity& entities, double x, double y);
        bool CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) override;
        EntityGraphics* GenerateGraphicComponent() override;
        void GFX_UpdateState(EntityGraphics_Gold* graphic);
        void Debug_Draw(SimpleRenderer& rend) override;
};
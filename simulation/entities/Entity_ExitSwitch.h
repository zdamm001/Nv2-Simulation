#pragma once

#include "Entity_Base.h"
#include "..\\..\\math\\vec2.h"
//#include "simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"
#include "Entity_ExitDoor.h"

class EntityGraphics_ExitSwitch;

class Entity_ExitSwitch : public Entity_Base {
    private:
        vec2 pos;
        double r;
        Entity_ExitDoor* door;
    public:
        Entity_ExitSwitch(Grid_Entity& entities, double x, double y, Entity_ExitDoor* door);
        Entity_ExitSwitch(Grid_Entity& entities, entitySave& entity, Entity_ExitDoor* door);
        bool CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) override;
        EntityGraphics* GenerateGraphicComponent() override;
        void GFX_UpdateState(EntityGraphics_ExitSwitch* graphic);
        void Debug_Draw(SimpleRenderer& rend) override;
        // ByteArray saveState() override;
        void saveState(entitySave& state) override;
};

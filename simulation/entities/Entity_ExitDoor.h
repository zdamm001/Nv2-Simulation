#pragma once

#include "Entity_Base.h"
#include "..\\..\\math\\vec2.h"
//#include "simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\colutils.h"
#include "..\\ninja\\Ninja.h"

class EntityGraphics_ExitDoor;

class Entity_ExitDoor : public Entity_Base {
    private:
        vec2 pos;
        double r;
        bool isOpen;
    public:
        Entity_ExitDoor(double x, double y);
        Entity_ExitDoor(Grid_Entity* entities, entitySave& entity);
        bool CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) override;
        void SWITCH_OpenTheExit(Grid_Entity* entities);
        bool SWITCH_IsOpen();
        EntityGraphics* GenerateGraphicComponent() override;
        void GFX_UpdateState(EntityGraphics_ExitDoor* graphic);
        void Debug_Draw(SimpleRenderer& rend) override;
        void saveState(entitySave& state) override;
};
#include "Entity_Door_Trap.h"

Entity_Door_Trap::Entity_Door_Trap(Grid_Entity& entities, Grid_Segment& segments, int segmentIndex, Segment* segment, Grid_Edges& edges, vector<int>& edgeIndices, bool isHorizontal, double x, double y)
    : Entity_Door_Base(entities, segments, segmentIndex, segment, edges, edgeIndices, isHorizontal, x, y, 12.0 * (5.0 / 12.0), true) {
}

void Entity_Door_Trap::OnCollision(Simulator* sim) {
    sim->objGrid.ENTITY_Remove(this);
    ChangeDoorState(false);
}

EntityGraphics* Entity_Door_Trap::GenerateGraphicComponent() {
    vec2 doorPos = GetDoorPos();
    //return new EntityGraphics_Door_Trap(this, doorPos.x, doorPos.y, GetDoorOrn(), trigger_pos.x, trigger_pos.y);
}

void Entity_Door_Trap::GFX_UpdateState(EntityGraphics* graphic) {
    if (IsDoorOpen()) {
        //graphic->anim = EntityGraphics_Door_Trap::ANIM_OPEN;
    }
    else {
        //graphic->anim = EntityGraphics_Door_Trap::ANIM_CLOSE;
    }
}

void Entity_Door_Trap::Debug_Draw(SimpleRenderer& rend) {
    Debug_Draw_Base(rend, IsDoorOpen());
    //rend.SetStyle(4, 0x882222, 10);
    seg->DebugDraw_NoStyle(rend);
}

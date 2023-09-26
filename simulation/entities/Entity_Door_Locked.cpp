#include "Entity_Door_Locked.h"

Entity_Door_Locked::Entity_Door_Locked(Grid_Entity& entities, Grid_Segment& segments, int segmentIndex, Segment* segment, Grid_Edges& edges, vector<int>& edgeIndices, bool isHorizontal, double x, double y)
    : Entity_Door_Base(entities, segments, segmentIndex, segment, edges, edgeIndices, isHorizontal, x, y, 12.0 * (5.0 / 12.0), false) {
}

void Entity_Door_Locked::OnCollision(Simulator* sim) {
    sim->objGrid.ENTITY_Remove(this);
    ChangeDoorState(true);
}

EntityGraphics* Entity_Door_Locked::GenerateGraphicComponent() {
    vec2 doorPos = GetDoorPos();
    //return new EntityGraphics_Door_Locked(this, doorPos.x, doorPos.y, GetDoorOrn(), trigger_pos.x, trigger_pos.y);
}

void Entity_Door_Locked::GFX_UpdateState(EntityGraphics* graphic) {
    if (IsDoorOpen()) {
        //graphic->anim = EntityGraphics_Door_Locked::ANIM_OPEN;
    }
    else {
        //graphic->anim = EntityGraphics_Door_Locked::ANIM_CLOSE;
    }
}

void Entity_Door_Locked::Debug_Draw(SimpleRenderer& rend) {
    Debug_Draw_Base(rend, !IsDoorOpen());
    //rend->SetStyle(4, 0x222288, 10);
    seg->DebugDraw_NoStyle(rend);
}

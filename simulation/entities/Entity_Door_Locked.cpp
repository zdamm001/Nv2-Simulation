#include "Entity_Door_Locked.h"
#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Door_Locked.h"

Entity_Door_Locked::Entity_Door_Locked(Grid_Entity& entities, Grid_Segment& segments, int segmentIndex, Segment* segment, Grid_Edges& edges, vector<int>& edgeIndices, bool isHorizontal, double x, double y)
    : Entity_Door_Base(entities, segments, segmentIndex, segment, edges, edgeIndices, isHorizontal, x, y, 12.0 * (5.0 / 12.0), false) {
}

Entity_Door_Locked::Entity_Door_Locked(Grid_Entity& entities, entitySave& entity, Grid_Segment& segments, Grid_Edges& edges)
    : Entity_Door_Base(entities, entity, segments, edges, 12.0 * (5.0 / 12.0)) {
    if (entity.is == false) entities.ENTITY_Add(trigger_pos, this);
}

void Entity_Door_Locked::OnCollision(Simulator* sim) {
    sim->objGrid.ENTITY_Remove(this);
    ChangeDoorState(true);
}

EntityGraphics* Entity_Door_Locked::GenerateGraphicComponent() {
    vec2 doorPos = GetDoorPos();
    return new EntityGraphics_Door_Locked(this, doorPos.x, doorPos.y, GetDoorOrn(), trigger_pos.x, trigger_pos.y);
}

void Entity_Door_Locked::GFX_UpdateState(EntityGraphics_Door_Locked* graphic) {
    if (IsDoorOpen()) {
        graphic->anim = EntityGraphics_Door_Locked::ANIM_OPEN;
    }
    else {
        graphic->anim = EntityGraphics_Door_Locked::ANIM_CLOSE;
    }
}

void Entity_Door_Locked::Debug_Draw(SimpleRenderer& rend) {
    Debug_Draw_Base(rend, !IsDoorOpen());
    //rend->SetStyle(4, 0x222288, 10);
    seg->DebugDraw_NoStyle(rend);
}

void Entity_Door_Locked::saveState(entitySave& state) {
    Entity_Door_Base::saveState(state);
    state.etype = edat::ETYPE_DOOR_LOCKED;
}

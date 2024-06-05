#include "Entity_Door_Regular.h"
#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Door_Regular.h"

Entity_Door_Regular::Entity_Door_Regular(Grid_Entity* entities, Grid_Segment* segments, int segmentIndex, Segment* segment, Grid_Edges* edges, vector<int>& edgeIndices, bool isHorizontal, double x, double y)
    : close_timer(0), Entity_Door_Base(entities, segments, segmentIndex, segment, edges, edgeIndices, isHorizontal, x, y, 12.0 * (5.0 / 6.0), false) {
}

Entity_Door_Regular::Entity_Door_Regular(Grid_Entity* entities, entitySave& entity, Grid_Segment* segments, Grid_Edges* edges)
    : close_timer(entity.state), Entity_Door_Base(entities, entity, segments, edges, 12.0 * (5.0 / 6.0)) {
    entities->ENTITY_Add(trigger_pos, this);
}

void Entity_Door_Regular::OnCollision(Simulator* sim) {
    close_timer = 0;
    if (!IsDoorOpen()) {
        ChangeDoorState(true);
    }
}

void Entity_Door_Regular::Think(Simulator* sim) {
    if (IsDoorOpen()) {
        ++close_timer;
        if (close_threshold < close_timer) {
            ChangeDoorState(false);
        }
    }
}

EntityGraphics* Entity_Door_Regular::GenerateGraphicComponent() {
    vec2 doorPos = GetDoorPos();
    return new EntityGraphics_Door_Regular(this, doorPos.x, doorPos.y, GetDoorOrn());
}

void Entity_Door_Regular::GFX_UpdateState(EntityGraphics_Door_Regular* graphic) {
    if (IsDoorOpen()) {
        graphic->anim = EntityGraphics_Door_Regular::ANIM_OPEN;
    } else {
        graphic->anim = EntityGraphics_Door_Regular::ANIM_CLOSE;
    }
}

void Entity_Door_Regular::Debug_Draw(SimpleRenderer& rend) {
    Debug_Draw_Base(rend, true);
    //rend.SetStyle(4, 0x228822, 10);
    seg->DebugDraw_NoStyle(rend);
}

void Entity_Door_Regular::saveState(entitySave& state) {
    Entity_Door_Base::saveState(state);
    state.etype = edat::ETYPE_DOOR_REGULAR;
    state.state = close_timer;
}

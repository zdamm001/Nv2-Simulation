#include "Entity_Door_Base.h"

Entity_Door_Base::Entity_Door_Base(Grid_Entity* entities, Grid_Segment* segments, int segmentIndex, Segment* segment, Grid_Edges* edges, vector<int>& edgeIndices, bool isHorizontal, double triggerPosX, double triggerPosY, double triggerRadius, bool isOpen)
    : trigger_pos(triggerPosX, triggerPosY), trigger_r(triggerRadius), seg_grid(segments), seg(segment), seg_index(segmentIndex), edge_grid(edges), edge_indices(edgeIndices), isHorizontal(isHorizontal), isOpen(isOpen) {
    if (!isOpen) {
        AddDoorToWorld();
    }
    entities->ENTITY_Add(trigger_pos, this);
}

Entity_Door_Base::Entity_Door_Base(Grid_Entity* entities, entitySave& entity, Grid_Segment* segments, Grid_Edges* edges, double triggerRadius)
    : trigger_pos(entity.pos), trigger_r(triggerRadius), seg_grid(segments), seg_index(entity.index), edge_grid(edges), edge_indices({entity.timer, entity.timer2}), isHorizontal(entity.is2), isOpen(entity.is) {
    seg = segments->DOOR_GetSegment(entity.index, entity.extra);
}

bool Entity_Door_Base::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    if (ninja != nullptr) {
        if (colutils::Overlap_Circle_Vs_Circle(trigger_pos, trigger_r, circlePosition, circleRadius)) {
            OnCollision(sim);
        }
    }
    return false;
}

void Entity_Door_Base::OnCollision(Simulator* sim) {};

bool Entity_Door_Base::IsDoorOpen() {
    return isOpen;
}

void Entity_Door_Base::ChangeDoorState(bool state) {
    if (isOpen == state) {
        return;
    }
    isOpen = state;
    if (isOpen) {
        RemoveDoorFromWorld();
    } else {
        AddDoorToWorld();
    }
}

void Entity_Door_Base::RemoveDoorFromWorld() {
    seg_grid->DOOR_RemoveSegment(seg_index, seg);
    for (size_t i = 0; i < edge_indices.size(); i++) {
        edge_grid->DOOR_DecrementEdge(edge_indices[i], isHorizontal);
    }
}

void Entity_Door_Base::AddDoorToWorld() {
    seg_grid->DOOR_AddSegment(seg_index, seg);
    for (size_t i = 0; i < edge_indices.size(); i++) {
        edge_grid->DOOR_IncrementEdge(edge_indices[i], isHorizontal);
    }
}

vec2 Entity_Door_Base::GetDoorPos() {
    AABB aabb = seg->GetAABB();
    return vec2(0.5 * (aabb.min.x + aabb.max.x), 0.5 * (aabb.min.y + aabb.max.y));
}

double Entity_Door_Base::GetDoorOrn() {
    if (isHorizontal) {
        return 0;
    }
    return M_PI / 2;
}

void Entity_Door_Base::Debug_Draw_Base(SimpleRenderer& rend, bool drawTrigger) {
    if (drawTrigger) {
        //rend->SetStyle(0, 0x882288, 30);
        //rend->DrawCircle(trigger_pos.x, trigger_pos.y, trigger_r);

        AABB aabb = seg->GetAABB();
        vec2 aabbCenter = vec2(0.5 * (aabb.max.x + aabb.min.x), 0.5 * (aabb.max.y + aabb.min.y));
        //rend->DrawLine(trigger_pos.x, trigger_pos.y, aabbCenter.x, aabbCenter.y);
    }

    if (!isOpen) {
        //rend->SetStyle(0, 0, 100);
        seg->DebugDraw_NoStyle(rend);
    }
}

void Entity_Door_Base::saveState(entitySave& state) {
    Entity_Base::saveState(state);
    state.pos = trigger_pos;
    state.index = seg_index;
    state.extra = seg_grid->DOOR_GetSegInnerIndex(seg_index, seg);
    state.timer = edge_indices[0];
    state.timer2 = edge_indices[1];
    state.is = isOpen;
    state.is2 = isHorizontal;
}
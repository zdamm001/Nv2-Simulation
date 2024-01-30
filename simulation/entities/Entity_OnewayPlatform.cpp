#include "Entity_OnewayPlatform.h"

Entity_OnewayPlatform::Entity_OnewayPlatform(Grid_Entity& entities, double x, double y, double nx, double ny)
    : pos(x, y), n(nx, ny), r(12) {
    entities.ENTITY_Add(pos, this);
}

Entity_OnewayPlatform::Entity_OnewayPlatform(Grid_Entity& entities, entitySave& entity)
    : pos(entity.pos), n(entity.n), r(12) {
    entities.ENTITY_Add(pos, this);
}

bool Entity_OnewayPlatform::CollideVsCircle_Physical(collision_result_physical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius) {
    double penetration = CalculatePenetration(circlePosition, circleVelocity, circleOldPosition, circleRadius, 0);
    if (penetration >= 0) {
        result.isHardCollision = true;
        result.nx = n.x;
        result.ny = n.y;
        result.pen = penetration;
        return true;
    }
    return false;
}

bool Entity_OnewayPlatform::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    if (ninja != nullptr) {
        double penetration = CalculatePenetration(circlePosition, circleVelocity, circleOldPosition, circleRadius, epsilon);
        if (penetration >= 0) {
            result.vec_x = n.x;
            result.vec_y = n.y;
            return true;
        }
    }
    return false;
}

double Entity_OnewayPlatform::CalculatePenetration(const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    double loc6 = circlePosition.x - pos.x;
    double loc7 = circlePosition.y - pos.y;
    double loc8 = r + circleRadius - fabs(-n.y * loc6 + n.x * loc7);

    if (loc8 > 0) {
        double loc9 = circleRadius + epsilon - fabs(n.x * loc6 + n.y * loc7);
        if (loc9 > 0) {
            double loc10 = n.x * circleVelocity.x + n.y * circleVelocity.y;
            if (loc10 <= 0) {
                double loc11 = circleOldPosition.x - pos.x;
                double loc12 = circleOldPosition.y - pos.y;
                double loc13 = circleRadius - (n.x * loc11 + n.y * loc12);
                if (loc13 <= 1.1) {
                    double pen = circleRadius - (n.x * loc6 + n.y * loc7);
                    if (pen < 0) {
                        return -1;
                    }
                    return pen;
                }
            }
        }
    }
    return -1;
}

EntityGraphics* Entity_OnewayPlatform::GenerateGraphicComponent() {
    return nullptr;
    //return new EntityGraphics_OnewayPlatform(pos.x, pos.y, atan2(n.y, n.x));
}

void Entity_OnewayPlatform::Debug_Draw(SimpleRenderer& rend) {
    //rend.SetStyle(0, 0, 100);
    //rend.DrawLine(pos.x - -n.y * r, pos.y - n.x * r, pos.x + -n.y * r, pos.y + n.x * r);
    //rend.DrawLine(pos.x, pos.y, pos.x + n.x * 4, pos.y + n.y * 4);
}

// ByteArray Entity_OnewayPlatform::saveState() {
//     ByteArray state;
//     state.writeByte(edat::STRUCTTYPE_ONEWAY);
//     state.writeDouble(pos.x);
//     state.writeDouble(pos.y);
//     state.writeDouble(n.x);
//     state.writeDouble(n.y);
//     return state;
// }

void Entity_OnewayPlatform::saveState(entitySave& state) {
    Entity_Base::saveState(state);
    state.etype = edat::ETYPE_ONEWAY;
    state.pos = pos;
    state.n = n;
}
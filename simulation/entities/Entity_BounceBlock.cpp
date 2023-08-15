#include "Entity_BounceBlock.h"

Entity_BounceBlock::Entity_BounceBlock(Grid_Entity& gridEntity, double x, double y)
  : pos(x, y),
    vel(0, 0),
    anchor(x, y),
    r(0.8 * 12),
    stiff(0.05 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
    damp(0.99),
    mass(0.2),
    isSleeping(true) {
    if (sim_globals::sim_rate == 60) {
        damp = 0.98;
    }
    gridEntity.ENTITY_Add(pos, this);
}

bool Entity_BounceBlock::CollideVsCircle_Physical(collision_result_physical& collisionResult, const vec2& circleCenter, const vec2& circleVelocity, const vec2& squareCenter, double circleRadius) {
    this->n.x = 0;
    this->n.y = 0;
    double penetration = colutils::Penetration_Square_vs_Point(this->pos, this->r + circleRadius, circleCenter, this->n);

    if (penetration != 0) {
        double impact = (1 - this->mass) * penetration;

        this->pos.x -= impact * this->n.x;
        this->vel.x -= impact * this->n.x;
        this->pos.y -= impact * this->n.y;
        this->vel.y -= impact * this->n.y;

        collisionResult.isHardCollision = false;
        collisionResult.nx = this->n.x;
        collisionResult.ny = this->n.y;
        collisionResult.pen = this->mass * penetration;

        return true;
    }

    return false;
}

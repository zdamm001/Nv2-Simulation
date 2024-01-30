#include "Entity_BounceBlock.h"

Entity_BounceBlock::Entity_BounceBlock(Grid_Entity& entities, double x, double y)
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
    entities.ENTITY_Add(pos, this);
}

Entity_BounceBlock::Entity_BounceBlock(Grid_Entity& entities, entitySave& entity)
  : pos(entity.pos),
    vel(entity.vel),
    anchor(entity.pos2),
    r(0.8 * 12),
    stiff(0.05 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
    damp(0.99),
    mass(0.2),
    isSleeping(true),
    n(entity.n) {
    if (sim_globals::sim_rate == 60) {
        damp = 0.98;
    }
    entities.ENTITY_Add(pos, this);
}

bool Entity_BounceBlock::CollideVsCircle_Physical(collision_result_physical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius) {
    this->n.x = 0;
    this->n.y = 0;
    double penetration = colutils::Penetration_Square_vs_Point(this->pos, this->r + circleRadius, circlePosition, this->n);

    if (penetration != 0) {
        double impact = (1 - this->mass) * penetration;

        this->pos.x -= impact * this->n.x;
        this->vel.x -= impact * this->n.x;
        this->pos.y -= impact * this->n.y;
        this->vel.y -= impact * this->n.y;

        result.isHardCollision = false;
        result.nx = this->n.x;
        result.ny = this->n.y;
        result.pen = this->mass * penetration;

        return true;
    }

    return false;
}

bool Entity_BounceBlock::CollideVsCircle_Logical(Simulator* sim, Ninja* ninja, collision_result_logical& result, const vec2& circlePosition, const vec2& circleVelocity, const vec2& circleOldPosition, double circleRadius, double epsilon) {
    if (ninja != nullptr) {
        this->n.x = 0;
        this->n.y = 0;
        double penetration = colutils::Penetration_Square_vs_Point(this->pos, epsilon + this->r + circleRadius, circlePosition, this->n);
        if (penetration != 0) {
            result.vec_x = this->n.x;
            result.vec_y = this->n.y;
            return true;
        }
    }
    return false;
}

void Entity_BounceBlock::Think(Simulator* sim) {
    if (!this->isSleeping) {
        double dx = this->anchor.x - this->pos.x;
        double dy = this->anchor.y - this->pos.y;
        double distanceSq = dx * dx + dy * dy;

        if (this->vel.LenSq() < 0.05 && distanceSq < 0.05) {
            this->pos.Copy(this->anchor);
            this->vel.x = 0;
            this->vel.y = 0;
            this->isSleeping = true;
        }
    }
}

void Entity_BounceBlock::Move(Simulator* sim) {
    this->vel.Scale(this->damp);
    this->pos.x += this->vel.x;
    this->pos.y += this->vel.y;
    double dx = this->anchor.x - this->pos.x;
    double dy = this->anchor.y - this->pos.y;
    dx *= this->stiff;
    dy *= this->stiff;
    this->pos.x += dx;
    this->pos.y += dy;
    this->vel.x += dx;
    this->vel.y += dy;
    sim->objGrid.ENTITY_Move(this->pos, this);
}

EntityGraphics* Entity_BounceBlock::GenerateGraphicComponent() {
    return nullptr;
    //return new EntityGraphics_BounceBlock(this);
}

void Entity_BounceBlock::GFX_UpdateState(EntityGraphics_BounceBlock* graphic) {
    //graphic->pos.x = this->pos.x;
    //graphic->pos.y = this->pos.y;
}

void Entity_BounceBlock::Debug_Draw(SimpleRenderer& rend) {
    if (this->isSleeping) {
        //rend.SetStyle(0, 0, 30);
    } else {
        //rend.SetStyle(0, 0, 100);
    }
    //rend.DrawSquare(this->pos.x, this->pos.y, this->r);
}

// ByteArray Entity_BounceBlock::saveState() {
//     ByteArray state;
//     state.writeByte(edat::STRUCTTYPE_BOUNCEBLOCK);
//     state.writeDouble(pos.x);
//     state.writeDouble(pos.y);
//     state.writeDouble(vel.x);
//     state.writeDouble(vel.y);
//     state.writeDouble(n.x);
//     state.writeDouble(n.y);
//     return state;
// }

void Entity_BounceBlock::saveState(entitySave& state) {
    Entity_Base::saveState(state);
    state.etype = edat::ETYPE_BOUNCEBLOCK;
    state.pos = pos;
    state.pos2 = anchor;
    state.vel = vel;
    state.n = n;
}
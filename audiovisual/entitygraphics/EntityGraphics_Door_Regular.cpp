#include "EntityGraphics_Door_Regular.h"
#include "../../simulation/entities/Entity_Door_Regular.h"

EntityGraphics_Door_Regular::EntityGraphics_Door_Regular(Entity_Door_Regular* entity, double x, double y, double rotation)
    : entity(entity), anim(ANIM_CLOSE) {
    mc_door = new MovieClip(); //new asset_gfx_door_regular();
    mc_door->x = x;
    mc_door->y = y;
    mc_door->rotation = rotation / M_PI * 180;
    //mc_door->gotoAndStop("closed");
}

EntityGraphics_Door_Regular::~EntityGraphics_Door_Regular() {
    delete mc_door;
}

void EntityGraphics_Door_Regular::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.push_back(mc_door);
}

void EntityGraphics_Door_Regular::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);
    if (anim != prevAnim) {
        if (anim == ANIM_CLOSE) {
            // mc_door->gotoAndPlay("close");
        } else if (anim == ANIM_OPEN) {
            // mc_door->gotoAndPlay("open");
        }
    }
}
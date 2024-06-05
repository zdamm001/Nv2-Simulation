#include "EntityGraphics_ExitDoor.h"
#include "..\\..\\simulation\\entities\\Entity_ExitDoor.h"

EntityGraphics_ExitDoor::EntityGraphics_ExitDoor(Entity_ExitDoor* entity, double x, double y)
    : entity(entity), anim(ANIM_CLOSED) {
    mc = new MovieClip(); //new asset_gfx_exitDoor()
    mc->x = x;
    mc->y = y;
    //mc->gotoAndStop("closed");
}

EntityGraphics_ExitDoor::~EntityGraphics_ExitDoor() {
    delete mc;
}

void EntityGraphics_ExitDoor::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.insert(displayObjects.begin(), mc);
}

void EntityGraphics_ExitDoor::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);
    if (anim != prevAnim) {
        if (anim == ANIM_OPEN) {
            //mc->gotoAndStop("open");
        }
    }
}
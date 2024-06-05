#include "EntityGraphics_ExitSwitch.h"
#include "..\\..\\simulation\\entities\\Entity_ExitSwitch.h"

EntityGraphics_ExitSwitch::EntityGraphics_ExitSwitch(Entity_ExitSwitch* entity, double x, double y)
    : entity(entity), anim(ANIM_CLOSED) {
    mc = new MovieClip(); //new asset_gfx_exitswitch()
    mc->x = x;
    mc->y = y;
    //mc->gotoAndStop("closed");
}

EntityGraphics_ExitSwitch::~EntityGraphics_ExitSwitch() {
    delete mc;
}

void EntityGraphics_ExitSwitch::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.insert(displayObjects.begin(), mc);
}

void EntityGraphics_ExitSwitch::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);
    if (anim != prevAnim) {
        if (anim == ANIM_OPEN) {
            //mc->gotoAndStop("open");
        }
    }
}
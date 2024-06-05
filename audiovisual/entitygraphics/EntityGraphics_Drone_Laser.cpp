#include "EntityGraphics_Drone_Laser.h"
#include "../../simulation/entities/Entity_Drone_Laser.h"

EntityGraphics_Drone_Laser::EntityGraphics_Drone_Laser(Entity_Drone_Laser* entity)
    : entity(entity), pos(0, 0), orn(0), anim(ANIM_MOVE), blast_pos(0, 0), blast_scale(0) {
    mc_body = new MovieClip(); // new asset_gfx_drone_laser();
    mc_eye = new MovieClip(); // new asset_gfx_drone_eye();
    mc_blast = new MovieClip(); // new asset_gfx_laser_blast();
    mc_beam = new Sprite();
    // mc_body->gotoAndStop("move");
}

EntityGraphics_Drone_Laser::~EntityGraphics_Drone_Laser() {
    delete mc_body;
    delete mc_eye;
    delete mc_blast;
    delete mc_beam;
}


void EntityGraphics_Drone_Laser::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.push_back(mc_beam);
    displayObjects.push_back(mc_body);
    displayObjects.push_back(mc_eye);
    displayObjects.push_back(mc_blast);
}

void EntityGraphics_Drone_Laser::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);
    mc_body->x = pos.x;
    mc_body->y = pos.y;
    mc_eye->x = pos.x;
    mc_eye->y = pos.y;
    mc_eye->rotation = orn / M_PI * 180;
    if (anim != prevAnim) {
        if (anim == ANIM_MOVE) {
            // mc_body->gotoAndStop("move");
        } else if (anim == ANIM_PREFIRE) {
            // mc_body->gotoAndPlay("prefire");
            mc_beam->visible = true;
            // mc_beam->graphics.clear();
            // mc_beam->graphics.lineStyle(0,13334137);
            // mc_beam->graphics.moveTo(pos.x, pos.y);
            // mc_beam->graphics.lineTo(blast_pos.x, blast_pos.y);
        } else if (anim == ANIM_POSTFIRE) {
            // mc_body->gotoAndPlay("postfire");
            mc_beam->visible = false;
            mc_blast->visible = false;
            // mc_blast->gotoAndStop(1);
        } else if (anim == ANIM_FIRING) {
            // mc_body->gotoAndStop("firing");
            // mc_beam->graphics.clear();
            // mc_beam->graphics.lineStyle(3,8921634);
            // mc_beam->graphics.moveTo(pos.x, pos.y);
            // mc_beam->graphics.lineTo(blast_pos.x, blast_pos.y);
            mc_blast->visible = true;
            // mc_blast->gotoAndPlay(1);
            mc_blast->x = blast_pos.x;
            mc_blast->y = blast_pos.y;
            mc_blast->scaleX = mc_blast->scaleY = 0;
        }
    }
    if (anim == ANIM_FIRING) {
        mc_blast->scaleX = mc_blast->scaleY = blast_scale / 100;
    }
}
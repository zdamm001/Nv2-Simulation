#include "EntityGraphics_Ninja.h"
#include "../../simulation/ninja/Ninja.h"

EntityGraphics_Ninja::EntityGraphics_Ninja(Ninja* entity, unsigned int color)
    : entity(entity), pos(0, 0), vel(0), orn(0), facing(1), anim(ANIM_STANDING),
      run_anim_leftovers(0), scaling_factor(0.2), prev_frame(1) {
    sndLoopMC = new MovieClip(); // new asset_sfx_playerLoopMC();
    sndMC = new MovieClip(); // new asset_sfx_playerMC();
    mc_sprite = new MovieClip(); // new asset_gfx_ninja();
    //mc_sprite->gotoAndPlay("STAND");

    ragdoll_mcList.resize(5);
    ragdoll_posList.resize(5);
    ragdoll_lenList.resize(5);
    ragdoll_ornList.resize(5);
    ragdoll_flipList.resize(5);

    ragdoll_mcList[RAGDOLL_BODY] = new MovieClip(); // new asset_gfx_ragdoll_body();
    ragdoll_mcList[RAGDOLL_ARM_R] = new MovieClip(); // new asset_gfx_ragdoll_arm();
    ragdoll_mcList[RAGDOLL_ARM_L] = new MovieClip(); // new asset_gfx_ragdoll_arm();
    ragdoll_mcList[RAGDOLL_LEG_R] = new MovieClip(); // new asset_gfx_ragdoll_leg();
    ragdoll_mcList[RAGDOLL_LEG_L] = new MovieClip(); // new asset_gfx_ragdoll_leg();

    ragdoll_flipList[RAGDOLL_BODY] = -1;
    ragdoll_flipList[RAGDOLL_ARM_R] = 1;
    ragdoll_flipList[RAGDOLL_ARM_L] = 1;
    ragdoll_flipList[RAGDOLL_LEG_R] = -1;
    ragdoll_flipList[RAGDOLL_LEG_L] = -1;

    //ColorTransform colorTransform(color);
    //mc_sprite->transform.colorTransform = colorTransform;

    for (size_t i = 0; i < ragdoll_mcList.size(); ++i) {
        //ragdoll_mcList[i]->transform.colorTransform = colorTransform;
    }
}

EntityGraphics_Ninja::~EntityGraphics_Ninja() {
    delete sndLoopMC;
    delete sndMC;
    delete mc_sprite;
    delete ragdoll_mcList[RAGDOLL_BODY];
    delete ragdoll_mcList[RAGDOLL_ARM_R];
    delete ragdoll_mcList[RAGDOLL_ARM_L];
    delete ragdoll_mcList[RAGDOLL_LEG_R];
    delete ragdoll_mcList[RAGDOLL_LEG_L];
}

void EntityGraphics_Ninja::HACKY_PlayOneshotSound(string soundName) {
    //sndMC->gotoAndPlay(soundName);
}

bool EntityGraphics_Ninja::hasValidPose() {
    return false;
    //return mc_sprite->shoulder && mc_sprite->pelvis && mc_sprite->handR && mc_sprite->handL && mc_sprite->footR && mc_sprite->footL;
}

void EntityGraphics_Ninja::NINJA_GetCurrentPose(vector<vec2>& posePos, vector<vec2>& poseVel) {
    int curr_frame = mc_sprite->currentFrame;
    //posePos[0] = vec2(mc_sprite->shoulder.x, mc_sprite->shoulder.y);
    //posePos[1] = vec2(mc_sprite->pelvis.x, mc_sprite->pelvis.y);
    //posePos[2] = vec2(mc_sprite->handR.x, mc_sprite->handR.y);
    //posePos[3] = vec2(mc_sprite->handL.x, mc_sprite->handL.y);
    //posePos[4] = vec2(mc_sprite->footR.x, mc_sprite->footR.y);
    //posePos[5] = vec2(mc_sprite->footL.x, mc_sprite->footL.y);

    //mc_sprite->gotoAndStop(prev_frame);

    //poseVel[0] = vec2(posePos[0].x - mc_sprite->shoulder.x, posePos[0].y - mc_sprite->shoulder.y);
    //poseVel[1] = vec2(posePos[1].x - mc_sprite->pelvis.x,   posePos[1].y - mc_sprite->pelvis.y);
    //poseVel[2] = vec2(posePos[2].x - mc_sprite->handR.x,    posePos[2].y - mc_sprite->handR.y);
    //poseVel[3] = vec2(posePos[3].x - mc_sprite->handL.x,    posePos[3].y - mc_sprite->handL.y);
    //poseVel[4] = vec2(posePos[4].x - mc_sprite->footR.x,    posePos[4].y - mc_sprite->footR.y);
    //poseVel[5] = vec2(posePos[5].x - mc_sprite->footL.x,    posePos[5].y - mc_sprite->footL.y);
         

    for (int i = 0; i < 6; ++i) {
        posePos[i].Scale(scaling_factor);
        poseVel[i].Scale(scaling_factor);
    }
}

void EntityGraphics_Ninja::RegisterGraphics(vector<DisplayObject*>& displayObjects) {
    displayObjects.push_back(mc_sprite);
    for (size_t i = 0; i < ragdoll_mcList.size(); ++i) {
        displayObjects.push_back(ragdoll_mcList[i]);
    }
}

void EntityGraphics_Ninja::Hide() {
    mc_sprite->visible = false;
    for (size_t i = 0; i < ragdoll_mcList.size(); ++i) {
        ragdoll_mcList[i]->visible = false;
    }
}

void EntityGraphics_Ninja::UpdateState() {
    int prevAnim = anim;
    entity->GFX_UpdateState(this);

    if (anim == ANIM_OFF) {
        mc_sprite->visible = false;
        for (size_t i = 0; i < ragdoll_mcList.size(); ++i) {
            ragdoll_mcList[i]->visible = false;
        }
    } else if (anim == ANIM_DEAD) {
        //sndLoopMC->gotoAndPlay("wallslide_stop");
        //sndLoopMC->gotoAndPlay("skid_stop");
        mc_sprite->visible = false;
        for (size_t i = 0; i < ragdoll_mcList.size(); ++i) {
            ragdoll_mcList[i]->visible = true;
            ragdoll_mcList[i]->x = ragdoll_posList[i].x;
            ragdoll_mcList[i]->y = ragdoll_posList[i].y;
            ragdoll_mcList[i]->scaleX = scaling_factor;
            ragdoll_mcList[i]->scaleY = ragdoll_flipList[i] * facing * scaling_factor;
            ragdoll_mcList[i]->rotation = ragdoll_ornList[i] / M_PI * 180;
            //ragdoll_mcList[i]->gotoAndStop(1 + static_cast<int>(100 * ragdoll_lenList[i]));
        }
    } else {
        prev_frame = mc_sprite->currentFrame;
        mc_sprite->visible = true;
        for (size_t i = 0; i < ragdoll_mcList.size(); ++i) {
            ragdoll_mcList[i]->visible = false;
        }
        mc_sprite->x = pos.x;
        mc_sprite->y = pos.y;
        mc_sprite->scaleX = facing * scaling_factor;
        mc_sprite->scaleY = scaling_factor;
        mc_sprite->rotation = orn / M_PI * 180;
        if (anim != prevAnim) {
            if (prevAnim == ANIM_WALLSLIDING) {
                //sndLoopMC->gotoAndPlay("wallslide_stop");
            } else if (prevAnim == ANIM_SKIDDING) {
                //sndLoopMC->gotoAndPlay("skid_stop");
            }
            if (anim == ANIM_STANDING) {
                //mc_sprite->gotoAndPlay("STAND");
            } else if (anim == ANIM_SKIDDING) {
                //mc_sprite->gotoAndStop("SKID");
                //sndLoopMC->soundTransform.volume = 0;
                //sndLoopMC->gotoAndPlay("skid_start");
            } else if (anim == ANIM_WALLSLIDING) {
                //mc_sprite->gotoAndStop("WALLSLIDE");
                //sndLoopMC->soundTransform.volume = 0;
                //sndLoopMC->gotoAndPlay("wallslide_start");
            } else if (anim == ANIM_RUNNING) {
                //mc_sprite->gotoAndStop("RUN");
            } else if (anim == ANIM_CELEBRATING) {
                int celebrationIndex = rand() % 9 + 1;
                //mc_sprite->gotoAndPlay("CELEBRATE_NEW" + to_string(celebrationIndex));
            }
        }
        if (anim == ANIM_WALLSLIDING) {
            //sndLoopMC->soundTransform = new SoundTransform(min(1.0, abs(vel * 0.7)));
        } else if (anim == ANIM_SKIDDING) {
            //sndLoopMC->soundTransform = new SoundTransform(min(1.0, abs(vel)));;
        }
        if (anim == ANIM_INAIR) {
            int middleFrame = 94;
            double minVel = -1 * (40.f / 60);
            double maxVel = 2.5 * (40.f / 60);
            double velFactor = 0;
            if (vel < 0) {
                if (vel < minVel) {
                    velFactor = -1;
                } else {
                    velFactor = -(vel / minVel);
                }
            } else if (vel > maxVel) {
                velFactor = 1;
            } else {
                velFactor = sqrt(vel / maxVel);
            }
            int animationIndex = static_cast<int>(floor(velFactor * 9));
            //mc_sprite->gotoAndStop(middleFrame + animationIndex);
        } else if (anim == ANIM_RUNNING) {
            int startFrame = 13;
            int frameCount = 72;
            double velScale = 0.9;
            int frameOffset = mc_sprite->currentFrame - startFrame;
            double frameChangeWithLeftovers = (vel / velScale) + run_anim_leftovers;
            int frameChange = static_cast<int>(floor(frameChangeWithLeftovers));
            run_anim_leftovers = frameChangeWithLeftovers - frameChange;
            int newFrameOffset = (frameOffset + frameChange) % frameCount;
            //mc_sprite->gotoAndStop(startFrame + newFrameOffset);
        }
    }
}
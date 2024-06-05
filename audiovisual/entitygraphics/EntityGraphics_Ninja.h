#pragma once
#include <vector>

#include "..\\..\\math\\vec2.h"
#include "EntityGraphics.h"

class Ninja;

class EntityGraphics_Ninja : public EntityGraphics {
    public:
        static const int ANIM_STANDING = 0;
        static const int ANIM_RUNNING = 1;
        static const int ANIM_SKIDDING = 2;
        static const int ANIM_INAIR = 3;
        static const int ANIM_WALLSLIDING = 4;
        static const int ANIM_DEAD = 5;
        static const int ANIM_CELEBRATING = 6;
        static const int ANIM_OFF = 7;

        static const int RAGDOLL_BODY = 0;
        static const int RAGDOLL_ARM_R = 1;
        static const int RAGDOLL_ARM_L = 2;
        static const int RAGDOLL_LEG_R = 3;
        static const int RAGDOLL_LEG_L = 4;
    private:
        Ninja* entity;
        MovieClip* sndLoopMC;
        MovieClip* sndMC;
        MovieClip* mc_sprite;
        vector<MovieClip*> ragdoll_mcList;
    public:
        vector<vec2> ragdoll_posList;
        vector<double> ragdoll_lenList;
        vector<double> ragdoll_ornList;
    private:
        vector<double> ragdoll_flipList;
    public:
        vec2 pos;
        double vel;
        double orn;
        int anim;
        int facing;
    private:
        double run_anim_leftovers;
        double scaling_factor;
        int prev_frame;
    public:
        EntityGraphics_Ninja(Ninja* entity, unsigned int color);
        virtual ~EntityGraphics_Ninja();
        virtual void RegisterGraphics(vector<DisplayObject*>& displayObjects) override;
        void HACKY_PlayOneshotSound(string soundName);
        bool hasValidPose();
        void NINJA_GetCurrentPose(vector<vec2>& posePos, vector<vec2>& poseVel);
        void Hide();
        virtual void UpdateState() override;
};
#pragma once

#include "Entity_Drone_Base.h"
//#include "..\\..\\math\\vec2.h"
//#include "simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Entity.h"
#include "entity_helpers.h"

class Entity_Drone_Shooter_Base : public Entity_Drone_Base {
    protected:
        static const int FIRING_STATE_IDLE = 0;
        static const int FIRING_STATE_PREFIRING = 1;
        static const int FIRING_STATE_FIRING = 2;
        static const int FIRING_STATE_POSTFIRING = 3;
    private:
        static vec2 zero_vec;
        int prefire_delay;
        int postfire_delay;
        int firing_timer;
        int CUR_FIRING_STATE;
        int targetIndex;
    public:
        Entity_Drone_Shooter_Base(Grid_Entity& entities, double x, double y, double speed, unsigned int facingDirection, unsigned int moveType, int prefireDelay, int postfireDelay);
        void Move(Simulator* sim) override final;
    protected:
        virtual int GetFiringState() final;
    public:
        void Think(Simulator* sim) override final;
    private:
        virtual void Internal_StartPrefiring(Simulator* sim, int ninjaID, const vec2& ninjaPos) final;
        virtual void Internal_StartFiring(Simulator* sim, const vec2& ninjaPos, const vec2& ninjaVel) final;
        virtual void Internal_StartPostfiring(Simulator* sim) final;
        virtual void Internal_StartIdling() final;
    protected:
        virtual void Start_Prefiring(Simulator* sim, const vec2& ninjaPos);
        virtual void Update_Prefiring(Simulator* sim, const vec2& ninjaPos);
        virtual void Start_Firing(Simulator* sim, const vec2& ninjaPos, const vec2& ninjaVel);
        virtual bool Update_Firing(Simulator* sim);
        virtual void Start_Postfiring(Simulator* sim);
    public:
        void Debug_Draw(SimpleRenderer& rend) override;
};
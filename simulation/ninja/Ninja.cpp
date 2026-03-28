#include "Ninja.h"
#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Ninja.h"
#include "Ragdoll.h"

const unsigned int Ninja::PSTATE_STANDING = 0;
const unsigned int Ninja::PSTATE_RUNNING = 1;
const unsigned int Ninja::PSTATE_SKIDDING = 2;
const unsigned int Ninja::PSTATE_JUMPING = 3;
const unsigned int Ninja::PSTATE_FALLING = 4;
const unsigned int Ninja::PSTATE_WALLSLIDING = 5;
const unsigned int Ninja::PSTATE_DEAD = 6;
const unsigned int Ninja::PSTATE_AWAITINGDEATH = 7;
const unsigned int Ninja::PSTATE_CELEBRATING = 8;
const unsigned int Ninja::PSTATE_DISABLED = 9;

vector<string> Ninja::PSTATE_TO_STRING(10);

void Ninja::Initialize() {
    PSTATE_TO_STRING[PSTATE_STANDING] = "standing";
    PSTATE_TO_STRING[PSTATE_RUNNING] = "running";
    PSTATE_TO_STRING[PSTATE_SKIDDING] = "skidding";
    PSTATE_TO_STRING[PSTATE_JUMPING] = "jumping";
    PSTATE_TO_STRING[PSTATE_FALLING] = "falling";
    PSTATE_TO_STRING[PSTATE_WALLSLIDING] = "wallsliding";
    PSTATE_TO_STRING[PSTATE_DEAD] = "dead";
    PSTATE_TO_STRING[PSTATE_AWAITINGDEATH] = "waiting to die";
    PSTATE_TO_STRING[PSTATE_CELEBRATING] = "celebration";
    PSTATE_TO_STRING[PSTATE_DISABLED] = "disabled";
}

Ninja::Ninja(int pID, InputSource_Base* input, double x, double y, unsigned int color)
    : pID(pID), 
      inputsource(input), 
      gfxColor(color), 
      pos(x, y), 
      vel(0, 0),
      oldpos(0, 0), 
      r(10), 
      impulse_scale(40.0 / sim_globals::sim_rate),
      groundAccel(0.15 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
      airAccel(0.1 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
      normGrav(0.15 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
      jumpGrav(0.025 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
      normDrag(pow(0.99, 40.0 / sim_globals::sim_rate)),
      winDrag(pow(0.8, 40.0 / sim_globals::sim_rate)),
      wallFriction(pow(0.87, 40.0 / sim_globals::sim_rate)),
      skidFriction(pow(0.92, 40.0 / sim_globals::sim_rate)),
      standFriction(pow(0.8, 40.0 / sim_globals::sim_rate)),
      facingDir(1), 
      jumpAmt(1),
      jump_y_bias(2), 
      max_jump_time(30 * (sim_globals::sim_rate / 40)),
      jumptimer(0), 
      wasJdown(false),
      WAS_IN_AIR(false), 
      oldv(0, 0), 
      IN_AIR(false), 
      NEAR_WALL(false), 
      wallN(0, 0), 
      floorN(0, -1),
      fcount(1), 
      fvec(0, 0),
      raggy(new Ragdoll),
      ninja_gfx(nullptr), 
      crush_threshold(0.05),
      crush_dist(0), 
      crush_flag(false), 
      death_type(sim_globals::DEATHTYPE_TIME) {
    maxspeedAir = r * 0.5 * (40.0 / sim_globals::sim_rate);
    maxspeedGround = r * 0.5 * (40.0 / sim_globals::sim_rate);
    g = normGrav;
    d = normDrag;
    curState = PSTATE_DISABLED;
    terminal_vel = r * 0.9 * (40.0 / sim_globals::sim_rate);
    rcount = lcount = jcount = 0;
}

Ninja::Ninja(ninjaSave& ninjaState, InputSource_Base* input)
    : pID(ninjaState.pID), 
      inputsource(input), 
      gfxColor(ninjaState.gfxColor), 
      pos(ninjaState.pos), 
      vel(ninjaState.vel),
      oldpos(ninjaState.oldpos), 
      r(10), 
      impulse_scale(40.0 / sim_globals::sim_rate),
      groundAccel(0.15 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
      airAccel(0.1 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
      normGrav(0.15 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
      jumpGrav(0.025 * (40.0 / sim_globals::sim_rate) * (40.0 / sim_globals::sim_rate)),
      normDrag(pow(0.99, 40.0 / sim_globals::sim_rate)),
      winDrag(pow(0.8, 40.0 / sim_globals::sim_rate)),
      wallFriction(pow(0.87, 40.0 / sim_globals::sim_rate)),
      skidFriction(pow(0.92, 40.0 / sim_globals::sim_rate)),
      standFriction(pow(0.8, 40.0 / sim_globals::sim_rate)),
      facingDir(1), 
      jumpAmt(1),
      jump_y_bias(2), 
      max_jump_time(30 * (sim_globals::sim_rate / 40)),
      jumptimer(ninjaState.jumptimer), 
      wasJdown(ninjaState.wasJdown),
      WAS_IN_AIR(false), 
      oldv(0, 0), 
      IN_AIR(ninjaState.inAir), 
      NEAR_WALL(ninjaState.nearWall), 
      wallN(ninjaState.wallN), 
      floorN(0, -1),
      fcount(1), 
      fvec(0, 0),
      raggy(new Ragdoll),
      ninja_gfx(nullptr), 
      crush_threshold(0.05),
      crush_dist(0), 
      crush_flag(false), 
      death_type(sim_globals::DEATHTYPE_TIME) {
    maxspeedAir = r * 0.5 * (40.0 / sim_globals::sim_rate);
    maxspeedGround = r * 0.5 * (40.0 / sim_globals::sim_rate);
    g = ninjaState.g;
    d = ninjaState.d;
    curState = ninjaState.curState;
    terminal_vel = r * 0.9 * (40.0 / sim_globals::sim_rate);
    rcount = lcount = jcount = 0;
}

Ninja::~Ninja() {
    delete inputsource;
    delete ninja_gfx;
    delete raggy;
}

void Ninja::DEBUG_SetPosVel(const vec2& pos, const vec2& vel) {
    if (this->curState == PSTATE_DEAD) {
        this->raggy->TESTING_SetPosVel(pos, vel);
    } else {
        this->pos = pos;
        this->vel = vel;
    }
}

void Ninja::DEBUG_Respawn(const vec2& pos) {
    this->curState = PSTATE_STANDING;
    this->pos.x = pos.x;
    this->pos.y = pos.y;
    this->vel.x = 0;
    this->vel.y = 0;
    this->g = this->normGrav;
    this->d = this->normDrag;
}

int Ninja::GetIndex() {
    return pID;
}

vec2 Ninja::GetPos() {
    public_pos.Copy(pos);
    return public_pos;
}

vec2 Ninja::GetVel() {
    public_vel.Copy(vel);
    return public_vel;
}

double Ninja::GetRadius() {
    return r;
}

bool Ninja::IsDead() {
    return curState == PSTATE_DEAD || curState == PSTATE_DISABLED;
}

Ragdoll* Ninja::DEBUG_GetRagdoll() {
    return raggy;
}

void Ninja::APP_Enable() {
    curState = PSTATE_STANDING;
}

void Ninja::APP_Disable() {
    curState = PSTATE_DISABLED;
}

void Ninja::Integrate() {
    if (curState != PSTATE_DISABLED) {
        if (curState == PSTATE_DEAD) {
            raggy->Integrate(normGrav);
        } else {
            vel.x *= d;
            vel.y *= d;
            vel.y += g;
            pos.x += vel.x;
            pos.y += vel.y;
        }
    }
}

void Ninja::PreCollision() {
    if (curState != PSTATE_DISABLED) {
        if (curState == PSTATE_DEAD) {
            raggy->PreCollision();
        } else {
            oldv.x = vel.x;
            oldv.y = vel.y;
            fcount = 0;
            fvec.x = 0;
            fvec.y = 0;
            crush_vec.x = 0;
            crush_vec.y = 0;
            crush_dist = 0;
            crush_flag = false;
        }
    }
}

void Ninja::SolveInternalConstraints() {
    if(curState == PSTATE_DEAD) {
        raggy->SolveConstraints();
    }
}

void Ninja::PostCollision(Simulator* sim) {
    if (curState != PSTATE_DISABLED) {
        if (curState == PSTATE_DEAD) {
            raggy->PostCollision(sim);
        } else {
            oldpos.Copy(pos);
            double epsilon = 0.1;
            wallList_X.clear();
            wallList_Y.clear();
            result_logical.Clear();
            sim->objGrid->GatherCellContentsInNeighbourhood(pos, objList);
            for (int i = 0; i < objList.size(); ++i) {
                Entity_Base* entity = objList[i];
                if (entity->CollideVsCircle_Logical(sim, this, result_logical, pos, vel, oldpos, r, epsilon)) {
                    if (result_logical.vec_y == 0) {
                        wallList_X.push_back(result_logical.vec_x);
                        wallList_Y.push_back(result_logical.vec_y);
                    }
                }
            }
            double effectiveRadius = r + epsilon;
            sim->segGrid->GatherCellContentsFromWorldspaceRegion(pos.x - effectiveRadius, pos.y - effectiveRadius, pos.x + effectiveRadius, pos.y + effectiveRadius, segList);
            for (int i = 0; i < segList.size(); ++i) {
                segList[i]->GetClosestPoint(pos, seg_cp);
                double dx = pos.x - seg_cp.x;
                double dy = pos.y - seg_cp.y;
                double distance = sqrt(dx * dx + dy * dy);
                if (dy == 0 && distance <= effectiveRadius && distance != 0) {
                    dx *= 1 / distance;
                    dy *= 1 / distance;
                    wallList_X.push_back(dx);
                    wallList_Y.push_back(dy);
                }
            }
            WAS_IN_AIR = IN_AIR;
            IN_AIR = true;
            NEAR_WALL = false;
            if (!wallList_X.empty()) {
                NEAR_WALL = true;
                wallN.x = wallList_X[0];
                wallN.y = 0;
            }
            if (fcount > 0) {
                IN_AIR = false;
                double fvecLength = fvec.Len();
                if (fvecLength == 0) {
                    floorN.x = 0;
                    floorN.y = -1;
                } else {
                    floorN.x = fvec.x / fvecLength;
                    floorN.y = fvec.y / fvecLength;
                }
                if (WAS_IN_AIR) {
                    double tileImpactVel = oldv.x * floorN.x + oldv.y * floorN.y - 2 * abs(floorN.y) * impulse_scale;
                    if (tileImpactVel < -terminal_vel) {
                        vel.Copy(oldv);
                        sim->Event_PlayerWasKilled(this, sim_globals::ENEMYTYPE_FALL, pos.x, pos.y, 0, 0);
                    }
                }
            }
            if (crush_flag && crush_dist > 0) {
                double crushMagnitude = crush_vec.Len();
                double crushRatio = crushMagnitude / crush_dist;
                if (crushRatio < crush_threshold) {
                    sim->Event_PlayerWasKilled(this, sim_globals::ENEMYTYPE_CRUSH, pos.x, pos.y, 0, 0);
                }
            }
        }
    }
}

void Ninja::RespondToCollision(double collisionNormalX, double collisionNormalY, double collisionPenetration, bool isHardCollision, bool isThwompCollision) {
    pos.x += collisionPenetration * collisionNormalX;
    pos.y += collisionPenetration * collisionNormalY;
    
    if (isThwompCollision) {
        crush_flag = true;
    }
    
    if (isThwompCollision || isHardCollision) {
        crush_vec.x += collisionPenetration * collisionNormalX;
        crush_vec.y += collisionPenetration * collisionNormalY;
        crush_dist += abs(collisionPenetration);
    }
    
    if (isHardCollision) {
        double velocityProjection = vel.x * collisionNormalX + vel.y * collisionNormalY;
        if (velocityProjection < 0) {
            vel.x -= velocityProjection * collisionNormalX;
            vel.y -= velocityProjection * collisionNormalY;
        }
    } else {
        vel.x += collisionPenetration * collisionNormalX;
        vel.y += collisionPenetration * collisionNormalY;
    }
    
    if (collisionNormalY < 0) {
        ++fcount;
        fvec.x += collisionNormalX;
        fvec.y += collisionNormalY;
    }
}

void Ninja::CollideVsObjects(Simulator* sim) {
    bool isThwompCollision = false;

    if (curState == PSTATE_DEAD) {
        raggy->CollideVsObjects(sim);
    } else {
        result_physical.Clear();
        sim->objGrid->GatherCellContentsInNeighbourhood(pos, objList);

        for (int i = 0; i < objList.size(); ++i) {
            Entity_Base* entity = objList[i];
            
            if (entity->CollideVsCircle_Physical(result_physical, pos, vel, oldpos, r)) {
                isThwompCollision = dynamic_cast<Entity_Thwomp*>(entity) != nullptr;
                RespondToCollision(result_physical.nx, result_physical.ny, result_physical.pen, result_physical.isHardCollision, isThwompCollision);
            }
        }
    }
}

void Ninja::CollideVsTiles(Simulator* sim) {
    int maxIterations = 32;
    
    if (curState == PSTATE_DEAD) {
        raggy->CollideVsTiles(sim);
    } else {
        int closestPointSign = 0;
        cp.x = 0;
        cp.y = 0;
        for (int iterationCount = 0; iterationCount < maxIterations && (closestPointSign = colutils::GetSingleClosestPoint_Signed(sim->segGrid, pos, r, cp)) != 0; ++iterationCount) {
            double deltaX = pos.x - cp.x;
            double deltaY = pos.y - cp.y;
            double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
            
            double penetration = r - closestPointSign * distance;
            
            if (penetration < 1e-7) {
                break;
            }
            
            if (distance == 0) {
                return;
            }
            
            deltaX /= distance;
            deltaY /= distance;
            RespondToCollision(deltaX, deltaY, closestPointSign * penetration, true, false);
        }
    }
}

void Ninja::Think(Simulator* sim, unsigned int frame_num) {
    vector<vec2> currentPosePos;
    vector<vec2> currentPoseVel;

    inputsource->Tick(frame_num);
    bool rightButtonDown = inputsource->IsButtonDown_Right();
    bool leftButtonDown = inputsource->IsButtonDown_Left();
    bool jumpButtonDown = inputsource->IsButtonDown_Jump();
    bool isNewJumpPress = jumpButtonDown && !wasJdown;
    wasJdown = jumpButtonDown;

    //NEW for debugging
    rcount = rcount * rightButtonDown + rightButtonDown;
    lcount = lcount * leftButtonDown + leftButtonDown;
    jcount = jcount * jumpButtonDown + jumpButtonDown;

    if (curState == PSTATE_DISABLED) {
        return;
    }
    if (curState == PSTATE_DEAD) {
        return;
    }
    if (curState == PSTATE_AWAITINGDEATH) {
        currentPosePos.clear();
        currentPoseVel.clear();
        if (ninja_gfx != nullptr && ninja_gfx->hasValidPose()) {
            currentPosePos.resize(6);
            currentPoseVel.resize(6);
            ninja_gfx->NINJA_GetCurrentPose(currentPosePos, currentPoseVel);
        }
        raggy->ActivateRagdoll(pos, vel, death_pos, death_force, currentPosePos, currentPoseVel);
        if (death_type == sim_globals::DEATHTYPE_EXPLOSIVE || death_type == sim_globals::DEATHTYPE_SUICIDE) {
            raggy->ExplodeRagdoll(sim);
        }
        //sim->HACKY_GetParticleManager().Spawn_BloodSpurt(death_pos.x, death_pos.y, death_force.x, death_force.y, 3 + static_cast<int>(floor(rand() / (RAND_MAX + 1.0) * 4)));
        bool randomSoundChoice = (rand() / static_cast<double>(RAND_MAX)) < 0.5;
        if (death_type == sim_globals::DEATHTYPE_EXPLOSIVE) {
            if (randomSoundChoice) {
                //ninja_gfx->HACKY_PlayOneshotSound("explode1");
            } else {
                //ninja_gfx->HACKY_PlayOneshotSound("explode2");
            }
        } else if (death_type == sim_globals::DEATHTYPE_FALL) {
            //ninja_gfx->HACKY_PlayOneshotSound("fall");
        } else if (death_type == sim_globals::DEATHTYPE_LASER) {
            //ninja_gfx->HACKY_PlayOneshotSound("laser");
        } else if (death_type == sim_globals::DEATHTYPE_ELECTRIC) {
            if (randomSoundChoice) {
                //ninja_gfx->HACKY_PlayOneshotSound("zap1");
            } else {
                //ninja_gfx->HACKY_PlayOneshotSound("zap2");
            }
        } else if (randomSoundChoice) {
            //ninja_gfx->HACKY_PlayOneshotSound("shot1");
        } else {
            //ninja_gfx->HACKY_PlayOneshotSound("shot2");
        }
        curState = PSTATE_DEAD;
        return;
    }
    if (curState == PSTATE_CELEBRATING) {
        if (IN_AIR) {
            d = normDrag;
            if (WAS_IN_AIR) {}
        } else {
            d = winDrag;
            if (WAS_IN_AIR) {}
        }
        return;
    }
    this->tempV.x = 0;
    this->tempV.y = 0;
    this->tempP.x = 0;
    this->tempP.y = 0;
    double velX = this->vel.x;
    double velY = this->vel.y;
    double moveDirection = 0.0;

    if (leftButtonDown) {
        moveDirection--;
    }
    if (rightButtonDown) {
        moveDirection++;
    }
    if (IN_AIR) {
        this->tempV.Copy(this->vel);
        double newVelX = velX + moveDirection * this->airAccel;
        if (abs(newVelX) < this->maxspeedAir) {
            velX = newVelX;
        }
        this->vel.x = velX;

        if (curState < 3) {
            this->ACTION_Fall();
            return;
        }
        if (curState == PSTATE_JUMPING) {
            this->jumptimer++;
            if (!jumpButtonDown || this->jumptimer > this->max_jump_time) {
                this->ACTION_Fall();
                return;
            }
            return;
        }
        if (curState == PSTATE_FALLING) {}

        if (NEAR_WALL) {
            if (isNewJumpPress) {
                double jumpDirX = 0;
                double jumpDirY = 0;
                if (curState == PSTATE_WALLSLIDING && moveDirection * this->wallN.x < 0) {
                    jumpDirX = 1;
                    jumpDirY = 0.5;
                } else {
                    jumpDirX = 1.5;
                    jumpDirY = 0.7;
                }
                //sim->HACKY_GetParticleManager().Spawn_JumpDust(this->pos.x - this->wallN.x * this->r, this->pos.y - this->wallN.y * this->r, this->wallN.x * 90);
                this->ACTION_Jump(this->wallN.x * jumpDirX, this->wallN.y - jumpDirY);
                return;
            }
            if (curState == PSTATE_WALLSLIDING) {
                if (moveDirection * this->wallN.x > 0) {
                    this->ACTION_Fall();
                    return;
                }
                double absVelY = abs(velY);
                double wallSlideFrictionForce = -this->wallFriction * absVelY;
                this->tempV.Copy(this->vel);
                this->vel.y *= this->wallFriction;
                //sim->HACKY_GetParticleManager().Spawn_WallDust(this->pos, this->r, this->wallN, min(4.0, absVelY));
                return;
            }
            if (velY > 0 && moveDirection * this->wallN.x < 0) {
                this->ACTION_Wallslide();
                return;
            }
        } else if (curState == PSTATE_WALLSLIDING) {
            this->ACTION_Fall();
            return;
        }
    }
    else {
        this->tempV.Copy(this->vel);
        double newGroundVelX = velX + moveDirection * this->groundAccel;
        if (abs(newGroundVelX) < this->maxspeedGround) {
            velX = newGroundVelX;
        }
        this->vel.x = velX;

        if (this->curState > 2) {
            //sim->HACKY_GetParticleManager().Spawn_LandDust(this->pos.x - this->floorN.x * this->r, this->pos.y - this->floorN.y * this->r, 90 + atan2(this->floorN.y, this->floorN.x) / M_PI * 180, abs(this->vel.x) + this->vel.y);
            //this->ninja_gfx->HACKY_PlayOneshotSound("land");

            if (velX * moveDirection > 0) {
                this->ACTION_Run(moveDirection);
                return;
            }
            this->ACTION_Skid();
            return;
        }
        if (isNewJumpPress) {
            //sim->HACKY_GetParticleManager().Spawn_JumpDust(this->pos.x - this->floorN.x * this->r, this->pos.y - this->floorN.y * this->r, 90 + atan2(this->floorN.y, this->floorN.x) / M_PI * 180);

            if (moveDirection * this->floorN.x < 0) {
                this->ACTION_Jump(0, -0.7);
                return;
            }
            this->ACTION_Jump(this->floorN.x, this->floorN.y);
            return;
        }

        if (this->curState != PSTATE_RUNNING) {
            if (this->curState == PSTATE_SKIDDING) {
                double skidForceMag = abs(velX * -this->floorN.y + velY * this->floorN.x); //bad var name
                double skidForceX = velX * skidForceMag; //bad var name
                
                if (skidForceX * moveDirection > 0) {
                    this->ACTION_Run(moveDirection);
                    return;
                }

                if (skidForceMag < 0.1 && this->floorN.x == 0) {
                    this->ACTION_Stand();
                    return;
                }

                double skidForceSign = 1; //bad var name
                if (skidForceX < 0) {
                    skidForceSign = -1;
                }

                double skidAngle = atan2(this->floorN.x, -this->floorN.y) * (180 / M_PI); //bad var name?

                //sim->HACKY_GetParticleManager().Spawn_FloorDust(this->pos, this->r, this->floorN, skidAngle, skidForceSign, skidForceMag);

                this->tempV.Copy(this->vel);

                if (velY < 0 && this->floorN.x != 0) {
                    double l35 = abs(velX * this->skidFriction - velX); //bad var name
                    double l36 = abs(l35 * this->floorN.y) * (this->floorN.y * this->floorN.y); //bad var name
                    double l37 = sqrt(velX * velX + velY * velY); //bad var name
                    double l38 = l37 - l36; //bad var name
                    velX /= l37;
                    velY /= l37;
                    velX *= l38;
                    velY *= l38;
                } else {
                    velX *= this->skidFriction;
                }

                this->vel.x = velX;
                this->vel.y = velY;
                return;
            }

            if (moveDirection != 0) {
                this->ACTION_Run(moveDirection);
                return;
            }

            double groundForceDot = velX * -this->floorN.y + velY * this->floorN.x; //bad var name
            if (abs(groundForceDot) >= 0.1) {
                this->ACTION_Skid();
                return;
            }

            this->tempV.Copy(this->vel);
            velX *= this->standFriction;
            this->vel.x = velX;
            this->vel.y = velY;
            return;
        }

        double floorForceDot = velX * -this->floorN.y + velY * this->floorN.x; //bad var name
        double floorForceMag = abs(floorForceDot); //bad var name
        double floorForceX = velX * floorForceMag; //bad var name

        if (moveDirection * floorForceX <= 0) {
            this->ACTION_Skid();
            return;
        }

        if (moveDirection * this->floorN.x < 0) {
            double wallDirX = -abs(this->floorN.x); //bad var name
            double wallDirY = this->floorN.y; //bad var name

            if (this->floorN.x < 0) {
                wallDirY = -this->floorN.y;
            }

            double wallForceMag = abs(this->floorN.y); //bad var name
            wallDirY *= 0.5 * wallForceMag; //bad var name
            wallDirX *= 0.5 * wallForceMag; //bad var name

            double newVelX = velX + wallDirY * this->groundAccel;
            double newVelY = velY + wallDirX * this->groundAccel;

            if (abs(newGroundVelX) < this->maxspeedGround) {
                velX = newVelX;
                velY = newVelY;
            }

            this->tempV.Copy(this->vel);
            this->vel.x = velX;
            this->vel.y = velY;
        }
    }
}

void Ninja::ACTION_Jump(double jumpDirX, double jumpDirY) {
    this->HELPER_ExitCurrentState();
    this->curState = PSTATE_JUMPING;
    this->g = this->jumpGrav;

    double velX = this->vel.x;
    double velY = this->vel.y;

    if (velX * jumpDirX < 0) {
        this->vel.x = 0;
    }
    if (velY * jumpDirY < 0) {
        this->vel.y = 0;
    }

    this->pos.x += jumpDirX * this->jumpAmt * this->impulse_scale;
    this->pos.y += jumpDirY * (this->jumpAmt + this->jump_y_bias) * this->impulse_scale;
    this->vel.x += jumpDirX * this->jumpAmt * this->impulse_scale;
    this->vel.y += jumpDirY * (this->jumpAmt + this->jump_y_bias) * this->impulse_scale;

    this->jumptimer = 0;
    //this->ninja_gfx->HACKY_PlayOneshotSound("jump");
}

void Ninja::ACTION_Fall() {
    HELPER_ExitCurrentState();
    curState = PSTATE_FALLING;
}

void Ninja::ACTION_Wallslide() {
    HELPER_ExitCurrentState();
    curState = PSTATE_WALLSLIDING;
}

void Ninja::ACTION_Skid() {
    HELPER_ExitCurrentState();
    curState = PSTATE_SKIDDING;
}

void Ninja::ACTION_Run(double moveDirection) {
    HELPER_ExitCurrentState();
    curState = PSTATE_RUNNING;
}

void Ninja::ACTION_Stand() {
    HELPER_ExitCurrentState();
    curState = PSTATE_STANDING;
}

void Ninja::ACTION_Die() {
    HELPER_ExitCurrentState();
    curState = PSTATE_AWAITINGDEATH;
}

void Ninja::ACTION_Win() {
    HELPER_ExitCurrentState();
    curState = PSTATE_CELEBRATING;
}

void Ninja::HELPER_ExitCurrentState() {
    if (curState == PSTATE_DEAD) {
        return;
    }
    if (curState == PSTATE_JUMPING) {
        g = normGrav;
    }
}

void Ninja::SIM_Launch(double launchForceX, double launchForceY) {
    if (curState == PSTATE_AWAITINGDEATH) {
        return;
    }
    pos.x += launchForceX * impulse_scale;
    pos.y += launchForceY * impulse_scale;
    vel.x = launchForceX * impulse_scale;
    vel.y = launchForceY * impulse_scale;
    fcount = 0;
    if (curState != PSTATE_CELEBRATING) {
        ACTION_Fall();
    }
}

bool Ninja::SIM_Kill(int enemyType, double deathPosX, double deathPosY, double deathForceX, double deathForceY) {
    if (curState == PSTATE_AWAITINGDEATH || curState == PSTATE_DISABLED) {
        return false;
    }
    death_pos.x = deathPosX;
    death_pos.y = deathPosY;
    death_force.x = deathForceX;
    death_force.y = deathForceY;
    death_type = sim_globals::ETYPE_TO_DTYPE[enemyType];
    ACTION_Die();
    return true;
}

bool Ninja::SIM_Win() {
    if (curState == PSTATE_DISABLED || curState == PSTATE_CELEBRATING || curState == PSTATE_AWAITINGDEATH || curState == PSTATE_DEAD) {
        return false;
    }
    ACTION_Win();
    return true;
}

EntityGraphics_Ninja* Ninja::GenerateGraphicComponent() {
    ninja_gfx = new EntityGraphics_Ninja(this, gfxColor);
    return ninja_gfx;
}

void Ninja::GFX_UpdateState(EntityGraphics_Ninja* graphics) {
    if (curState == PSTATE_DISABLED) {
        graphics->anim = EntityGraphics_Ninja::ANIM_OFF;
    } else if (curState == PSTATE_DEAD) {
        graphics->anim = EntityGraphics_Ninja::ANIM_DEAD;
        raggy->GFX_UpdateState(graphics);
    } else {
        graphics->pos.x = pos.x;
        graphics->pos.y = pos.y;

        if (curState == PSTATE_WALLSLIDING) {
            graphics->anim = EntityGraphics_Ninja::ANIM_WALLSLIDING;
            graphics->orn = 0;
            graphics->facing = -wallN.x;
            graphics->vel = vel.y;
        } else {
            if (IN_AIR) {
                graphics->anim = EntityGraphics_Ninja::ANIM_INAIR;
                graphics->vel = vel.y;

                if (curState == PSTATE_JUMPING) {
                    graphics->orn = 0;
                } else {
                    graphics->orn -= 0.1 * graphics->orn;
                }
            } else {
                graphics->orn = atan2(floorN.y, floorN.x) + 0.5 * M_PI;

                if (curState == PSTATE_RUNNING) {
                    graphics->anim = EntityGraphics_Ninja::ANIM_RUNNING;
                    graphics->vel = abs(vel.x * -floorN.y + vel.y * floorN.x);
                } else if (curState == PSTATE_SKIDDING) {
                    graphics->anim = EntityGraphics_Ninja::ANIM_SKIDDING;
                    graphics->vel = vel.x * -floorN.y + vel.y * floorN.x;
                } else if (curState == PSTATE_STANDING) {
                    graphics->anim = EntityGraphics_Ninja::ANIM_STANDING;
                } else if (curState == PSTATE_CELEBRATING) {
                    graphics->anim = EntityGraphics_Ninja::ANIM_CELEBRATING;
                }
            }

            if (vel.x < -0.01) {
                graphics->facing = -1;
            } else if (vel.x > 0.01) {
                graphics->facing = 1;
            }
        }
    }
}

void Ninja::Draw(SimpleRenderer& rend) {
    vec2 floorContactPoint;
    double angle, dir;

    if (curState == PSTATE_DEAD) {
        raggy->Draw(rend);
    } else {
        //rend.SetStyle(0, 0, 20);
        //rend.DrawCircle(oldpos.x, oldpos.y, r);

        //rend.SetStyle(0, 0, 100);
        //rend.DrawCircle(pos.x, pos.y, r);

        string stateStr = PSTATE_TO_STRING[curState];

        if (curState == PSTATE_CELEBRATING) {
            if (IN_AIR) {
                stateStr += " (in air)";
            } else {
                stateStr += " (on ground)";
            }
        }

        //rend.DrawStringAtPosition(stateStr, pos.x + r, pos.y + r);

        if (!IN_AIR) {
            //rend.SetStyle(0, 0x882222, 100);
            floorContactPoint.x = pos.x - floorN.x * r;
            floorContactPoint.y = pos.y - floorN.y * r;

            //rend.DrawSquare(floorContactPoint.x, floorContactPoint.y, 2);
            //rend.DrawLine(floorContactPoint.x, floorContactPoint.y, floorContactPoint.x + floorN.x * 8, floorContactPoint.y + floorN.y * 8);
        }

        angle = 0;
        dir = 1;

        if (curState == PSTATE_WALLSLIDING) {
            angle = 0;
            dir = -wallN.x;
        } else {
            if (curState == PSTATE_JUMPING) {
                angle = 0;
            }

            if (IN_AIR) {
                angle -= 0.1 * angle;
            } else {
                angle = atan2(floorN.y, floorN.x) + 0.5 * M_PI;
            }

            if (vel.x < 0) {
                dir = -1;
            } else {
                dir = 1;
            }
        }

        vec2 directionIndicator = vec2(cos(angle), sin(angle));
        directionIndicator.Scale(r * dir);

        //rend.SetStyle(0, 0, 100);
        //rend.DrawLine(pos.x, pos.y, pos.x + directionIndicator.x, pos.y + directionIndicator.y);
    }
}

unsigned int Ninja::NEW_GetState() const {
    return this->curState;
}

bool Ninja::NEW_GetInAir() const {
    return this->IN_AIR;
}

bool Ninja::NEW_GetNearWall() const {
    return this->NEAR_WALL;
}

// ByteArray Ninja::saveState() {
//     ByteArray state;
//     //inputsource->
//     state.writeDouble(pos.x);
//     state.writeDouble(pos.y);
//     state.writeDouble(vel.x);
//     state.writeDouble(vel.y);
//     state.writeDouble(oldpos.x);
//     state.writeDouble(oldpos.y);
//     state.writeDouble(g);
//     state.writeDouble(d);
//     state.writeUnsignedInt(curState);
//     state.writeDouble(jumptimer);
//     state.writeBoolean(wasJdown);
//     state.writeBoolean(IN_AIR);
//     state.writeBoolean(NEAR_WALL);
//     state.writeDouble(wallN.x);
//     state.writeDouble(wallN.y);
//     state.writeInt(pID);
//     state.writeUnsignedInt(gfxColor);
//     return state;
// }

void Ninja::saveState(ninjaSave& state) {
    inputsource->saveState(state.frames);
    state.pos = pos;
    state.vel = vel;
    state.oldpos = oldpos;
    state.g = g;
    state.d = d;
    state.curState = curState;
    state.jumptimer = jumptimer;
    state.wasJdown = wasJdown;
    state.inAir = IN_AIR;
    state.nearWall = NEAR_WALL;
    state.wallN = wallN;
    state.pID = pID;
    state.gfxColor = gfxColor;
    // maybe lrj count later
}
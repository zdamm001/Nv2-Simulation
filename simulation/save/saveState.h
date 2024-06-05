#pragma once

#include "..\\..\\math\\vec2.h"
#include "..\\..\\flash\\utils\\ByteArray.h"
#include "..\\..\\simulation\\collision\\Grid_Segment.h"
#include "..\\..\\simulation\\collision\\Grid_Edges.h"

//0 all
//2 => 3,trap,locked
//4 => 5,6,7,8,ZAP
//8 => 5,7

// struct entitySave {
//     int UID; //0
//     int grid_index; //0
//     vec2 pos; //149ABCDEFGH
//     vec2 vel; //1
//     vec2 n; //1DFH
//     vec2 trigger_pos; //2 pos2
//     Segment* seg; //2  ?
//     int seg_index; //2 INDEX
//     vector<int> edge_indices; //2 ?
//     bool isHorizontal; //2H
//     bool isOpen; //29 IS
//     int close_timer; //3 TIMER
//     double gfxorn; //4 SHOTTIMER
//     vec2 next_goal; //4 pos2
//     unsigned int facing_DIR; //4
//     unsigned int move_TYPE; //4
//     int chaingun_count; //5 EXTRA
//     int chaingun_timer; //5 TIMER STATE
//     vec2 chaingun_dir; //5 dir
//     vec2 chaingun_sweep; //5 VEL
//     bool isChasing; //6 IS
//     bool gfx_startedChasing; //6 idk if needed, Render may or may not be called during tick. called in same location as gold addition ISH
//     int laser_timer; //7 TIMER STATE
//     vec2 laser_dir; //7 dir
//     vec2 laser_hit_pos; //7 if needed then chaingun maybe too VEL
//     vec2 laser_hit_n; //7 same as above N
//     int firing_timer; //8 TIMER
//     int CUR_FIRING_STATE; //8 STATE
//     int targetIndex; //8GI INDEX
//     Entity_ExitDoor* door; //A ?
//     int CUR_STATE; //BGHI STATE
//     bool isCollected; //C IS
//     bool isExploded; //E IS
//     vec2 rocket_pos; //G pos2
//     vec2 rocket_dir; //G dir
//     double rocket_speed; //G VX
//     double rocket_accel; //G VY
//     double shot_timer; //GI
//     int gfx_PREV_STATE; //G EXTRA
//     int falldir; //H EXTRA
//     vec2 aim_pos; //I pos2
//     int aim_region; //I STATE
// };

struct entitySave {
    unsigned int etype;
    int UID;
    int gridIndex;
    vec2 pos;
    vec2 pos2;
    vec2 vel;
    vec2 dir;
    vec2 n;
    bool is;
    bool is2;
    unsigned int facingDir;
    unsigned int moveType;
    int index;
    int state;
    int timer;
    int timer2;
    double timer3;
    int extra;
};

struct ninjaSave {
    ByteArray frames;
    vec2 pos;
    vec2 vel;
    vec2 oldpos;
    double g;
    double d;
    unsigned int curState;
    double jumptimer;
    bool wasJdown;
    bool inAir;
    bool nearWall;
    vec2 wallN;
    int pID;
    unsigned int gfxColor;
};

struct appSave {
    int currentTicks;
    int ticksElapsed;
    string currentLevel;
    string levelName;
    unsigned int frameNum;
    vector<int> tiles;
    vector<ninjaSave> ninjaState;
    vector<entitySave> entityState;
    bool isCoopMode;
    bool isReplay;
    Grid_Segment* segGrid;
    Grid_Edges* edgeGrid;
};

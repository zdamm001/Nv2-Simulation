#pragma once

#include "Entity_Door_Base.h"
#include "..\\..\\math\\vec2.h"
//#include "..\\simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Edges.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\Grid_Segment.h"
#include "..\\collision\\Segment.h"

class EntityGraphics_Door_Regular;

class Entity_Door_Regular : public Entity_Door_Base {
    private:
        static const int close_threshold = 5;
        int close_timer;
    public:
        Entity_Door_Regular(Grid_Entity* entities, Grid_Segment* segments, int segmentIndex, Segment* segment, Grid_Edges* edges, vector<int>& edgeIndices, bool isHorizontal, double x, double y);
        Entity_Door_Regular(Grid_Entity* entities, entitySave& entity, Grid_Segment* segments, Grid_Edges* edges);
        void OnCollision(Simulator* sim) override;
        void Think(Simulator* sim) override;
        EntityGraphics* GenerateGraphicComponent() override;
        void GFX_UpdateState(EntityGraphics_Door_Regular* graphic);
        void Debug_Draw(SimpleRenderer& rend) override;
        void saveState(entitySave& state) override;
};

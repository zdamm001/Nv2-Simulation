#pragma once

#include "Entity_Door_Base.h"
//#include "..\\..\\audiovisual\\entitygraphics\\EntityGraphics_Door_Locked.h"
#include "..\\..\\math\\vec2.h"
//#include "..\\simpleFramework\\SimpleRenderer.h"
#include "..\\Simulator.h"
#include "..\\collision\\Grid_Edges.h"
#include "..\\collision\\Grid_Entity.h"
#include "..\\collision\\Grid_Segment.h"
#include "..\\collision\\Segment.h"
class EntityGraphics_Door_Locked;

class Entity_Door_Locked : public Entity_Door_Base {
    public:
        Entity_Door_Locked(Grid_Entity& entities, Grid_Segment& segments, int segmentIndex, Segment* segment, Grid_Edges& edges, vector<int>& edgeIndices, bool isHorizontal, double x, double y);
    protected:
        void OnCollision(Simulator* sim) override;
    public:
        EntityGraphics* GenerateGraphicComponent() override;
        void GFX_UpdateState(EntityGraphics* graphic);
        void Debug_Draw(SimpleRenderer& rend) override;
};

#pragma once
#include <vector>

#include "..\\..\\math\\vec2.cpp"
#include "..\\entities\\Entity_Base.cpp"
#include "Grid_Base.cpp"

class Grid_Entity : public Grid_Base {
    private:
        std::vector<std::vector<Entity_Base*>> cells;
};
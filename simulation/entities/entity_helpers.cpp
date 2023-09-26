#include "entity_helpers.h"

const vec2 entity_helpers::zero_vec = vec2(0, 0);
vector<int> entity_helpers::potentialList(0);

int entity_helpers::TryToAquireTarget(const vec2& pos, const vector<Ninja*>& playerList, Grid_Segment& segGrid) {
    potentialList.clear();
    
    vec2 temp_zero_vec(0, 0);
    for (int i = 0; i < playerList.size(); ++i) {
        if (!playerList[i]->IsDead()) {
            if (segGrid.RaycastVsPlayer(pos, playerList[i]->GetPos(), playerList[i]->GetRadius(), temp_zero_vec, temp_zero_vec)) {
                potentialList.push_back(i);
            }
        }
    }
    
    if (potentialList.size() > 0) {
        unsigned int closestPlayer = 0;
        double deltaX = playerList[potentialList[0]]->GetPos().x - pos.x;
        double deltaY = playerList[potentialList[0]]->GetPos().y - pos.y;
        double closestDistSq = deltaX * deltaX + deltaY * deltaY;
        for (int i = 1; i < potentialList.size(); ++i) {
            deltaX = playerList[potentialList[i]]->GetPos().x - pos.x;
            deltaY = playerList[potentialList[i]]->GetPos().y - pos.y;
            double currDistSq = deltaX * deltaX + deltaY * deltaY;
            
            if (currDistSq < closestDistSq) {
                closestPlayer = i;
                closestDistSq = currDistSq;
            }
        }
        return potentialList[closestPlayer];
    }
    
    return -1;
}
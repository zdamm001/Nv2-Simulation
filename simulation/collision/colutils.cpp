#include "colutils.h"

int colutils::getSingleClosestPoint_Signed(Grid_Segment& gridSegment, vec2& point, double radius, vec2& closestPointResult) {
    bool isPointBackfacing = false;
    double distanceSquared = 0.0;
    double closestDistanceSquared = 99999999.0;
    int closestDistanceSign = 0;

    gridSegment.GatherCellContentsFromWorldspaceRegion(point.x - radius, point.y - radius, point.x + radius, point.y + radius, segmentList);

    for (int i = 0; i < segmentList.size(); ++i) {
        isPointBackfacing = segmentList[i].GetClosestPoint_IsBackfacing(point, closestPoint);
        double deltaX = closestPoint.x - point.x;
        double deltaY = closestPoint.y - point.y;
        distanceSquared = deltaX * deltaX + deltaY * deltaY;

        if (!isPointBackfacing) {
            distanceSquared -= 0.1;
        }

        if (distanceSquared < closestDistanceSquared) {
            closestPointResult.Copy(closestPoint);
            closestDistanceSquared = distanceSquared;
            closestDistanceSign = (isPointBackfacing) ? -1 : 1;
        }
    }

    return closestDistanceSign;
}

double colutils::Penetration_Square_vs_Point(const vec2& squareCenter, double contactRadius, const vec2& pointPosition, vec2& penetrationNormal) {
    double dx = pointPosition.x - squareCenter.x;
    double dy = pointPosition.y - squareCenter.y;
    double penetrationY = contactRadius - abs(dy);

    if (penetrationY > 0) {
        double penetrationX = contactRadius - abs(dx);
        if (penetrationX > 0) {
            if (penetrationY <= penetrationX) {
                penetrationNormal.x = 0;
                penetrationNormal.y = (dy <= 0) ? -1.0 : 1.0;
                return penetrationY;
            } else {
                penetrationNormal.y = 0;
                penetrationNormal.x = (dx <= 0) ? -1.0 : 1.0;
                return penetrationX;
            }
        }
    }

    return 0.0;
}
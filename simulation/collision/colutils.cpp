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

            if (isPointBackfacing) {
                closestDistanceSign = -1;
            } else {
                closestDistanceSign = 1;
            }
        }
    }

    return closestDistanceSign;
}
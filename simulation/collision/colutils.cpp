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

bool colutils::Overlap_Circle_Vs_Segment(const vec2& circleCenter, double circleRadius, const vec2& segmentStart, const vec2& segmentEnd, double segmentLength) {
    double dx = circleCenter.x - segmentStart.x;
    double dy = circleCenter.y - segmentStart.y;

    double segmentDirectionX = (segmentEnd.x - segmentStart.x) / segmentLength;
    double segmentDirectionY = (segmentEnd.y - segmentStart.y) / segmentLength;

    double dotProduct = dx * segmentDirectionX + dy * segmentDirectionY;

    if (dotProduct <= 0) {
        closestPoint.Copy(segmentStart);
    } else if (dotProduct >= segmentLength) {
        closestPoint.Copy(segmentEnd);
    } else {
        closestPoint.x = segmentStart.x + dotProduct * segmentDirectionX;
        closestPoint.y = segmentStart.y + dotProduct * segmentDirectionY;
    }

    double dxToClosest = circleCenter.x - closestPoint.x;
    double dyToClosest = circleCenter.y - closestPoint.y;

    double distanceSquared = dxToClosest * dxToClosest + dyToClosest * dyToClosest;
    double radiusSquared = circleRadius * circleRadius;

    return (distanceSquared < radiusSquared);
}

bool colutils::Overlap_Circle_Vs_Circle(const vec2& center1, double radius1, const vec2& center2, double radius2) {
    double dx = center2.x - center1.x;
    double dy = center2.y - center1.y;

    double distanceSquared = dx * dx + dy * dy;
    double sumOfRadii = radius1 + radius2;

    if (distanceSquared < sumOfRadii * sumOfRadii) {
        return true;
    }

    return false;
}

double TimeOfIntersection_Circle_vs_Circle(const vec2& circleCenter1, const vec2& circleCenter2, const vec2& motionStart1, const vec2& motionStart2, double circleRadius) {
    double dx = circleCenter1.x - circleCenter2.x;
    double dy = circleCenter1.y - circleCenter2.y;

    double dxStart = motionStart1.x - motionStart2.x;
    double dyStart = motionStart1.y - motionStart2.y;

    double distanceSquaredEnd = dx * dx + dy * dy;
    double distanceSquaredStart = dxStart * dxStart + dyStart * dyStart;

    double velocityX = dx - dxStart;
    double velocityY = dy - dyStart;

    double velocitySquared = velocityX * velocityX + velocityY * velocityY;
    double sumOfRadiiSquared = (2 * circleRadius) * (2 * circleRadius);

    const double epsilon = 0.0001;
    if (distanceSquaredStart <= sumOfRadiiSquared) {
        return -1;
    }

    if (fabs(velocitySquared) < epsilon) {
        return 2;
    }

    double t = -(dxStart * velocityX + dyStart * velocityY) / velocitySquared;
    if (t >= 1 || t <= 0) {
        return 2;
    }

    double closestDistanceSquared = distanceSquaredStart + t * (distanceSquaredEnd - distanceSquaredStart);
    if (closestDistanceSquared < sumOfRadiiSquared) {
        return t;
    }

    return 2;
}

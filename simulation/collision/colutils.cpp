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

double colutils::TimeOfIntersection_Circle_vs_Circle(const vec2& circlePos1, const vec2& circleVel1, const vec2& circlePos2, const vec2& circleVel2, double totalRadius) {
    double velX = circleVel1.x - circleVel2.x;
    double velY = circleVel1.y - circleVel2.y;

    double posX = circlePos1.x - circlePos2.x;
    double posY = circlePos1.y - circlePos2.y;

    double a = velX * velX + velY * velY;
    double b = 2 * (posX * velX + posY * velY);
    double c = posX * posX + posY * posY - totalRadius * totalRadius;

    const double EPSILON = 0.0001;

    if (c <= 0) {
        return -1;
    } else {
        if (abs(a) < EPSILON) {
            return 2;
        } else {
            if (b >= 0) {
                return 2;
            } else {
                double discriminant = b * b - 4 * a * c;
                if (discriminant < 0) {
                    return 2;
                } else {
                    double d = -0.5 * (b - sqrt(discriminant));
                    double root_1 = d / a;
                    double root_2 = c / d;
                    return min(root_1, root_2);
                }
            }
        }
    }
}

double colutils::TimeOfIntersection_Point_vs_Lineseg(const vec2& pointPos, const vec2& pointVel, const vec2& segmentStart, const vec2& segmentEnd, double totalRadius) {
    double dx = segmentEnd.x - segmentStart.x;
    double dy = segmentEnd.y - segmentStart.y;
    double segmentLength = sqrt(dx * dx + dy * dy);
    dx /= segmentLength;
    dy /= segmentLength;
    double nx = -dy;
    double ny = dx;

    double px = pointPos.x - segmentStart.x;
    double py = pointPos.y - segmentStart.y;

    double pn = nx * px + ny * py;
    double vn = nx * pointVel.x + ny * pointVel.y;

    double pd = dx * px + dy * py;

    double relpos = abs(pn) - totalRadius;

    if (relpos < 0) {
        if (pd < 0 || pd > segmentLength) {
            return 2;
        } else {
            return -1;
        }
    } else {
        if (pn * vn >= 0) {
            return 2;
        } else {
            double t = relpos / abs(vn);
            double vd = dx * pointVel.x + dy * pointVel.y;
            double intersectionPos = pd + t * vd;
            if (intersectionPos < 0 || intersectionPos > segmentLength) {
                return 2;
            } else {
                return t;
            }
        }
    }
}

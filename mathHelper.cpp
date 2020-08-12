#include "mathHelper.h"

int nearestPerfectSquare(int n)
{
    int squareJumpAmount = 3;
    int curSquare = 1;
    int prevSquare = 0;
    while(curSquare < n)
    {
        prevSquare = curSquare;
        curSquare += squareJumpAmount;
        squareJumpAmount += 2;  // the difference between consecutive squares is odd integer
    }
    if(n - prevSquare > curSquare - n)
    {
        return curSquare;
    }
    else
    {
        return prevSquare;
    }
}

int isqrt(int n)
{
    return round(sqrt(n));
}

Point2D chunkIDtoPoint2D(int n)
{
    int s = nearestPerfectSquare(n);
    int sq = isqrt(s);
    if(s % 2 == 0)
    {
        if(n >= s)
        {
            return {sq/2, -sq/2 + n - s};
        }
        else
        {
            return {sq/2 - s + n, -sq/2};
        }
    }
    else
    {
        if(n >= s)
        {
            return {-(sq + 1)/2, (sq + 1)/2 - 1 - n + s};
        }
        else
        {
            return {-(sq + 1)/2 + s - n, (sq + 1)/2 - 1};
        }
    }
}

int point2DtoChunkID(Point2D p)
{
    int a = p.x;
    int b = p.z;
    // Bottom Zone
    if(b > 0 && a >= -b && a < b)
    {
        return 4*b*b + 3*b - a;
    }
    // Left Zone
    else if(a < 0 && b < -a && b >= a)
    {
        return 4*a*a + 3*a - b;
    }
    // Top Zone
    else if(b < 0 && a <= -b && a > b)
    {
        return 4*b*b + b + a;
    }
    // Right Zone
    else if(a > 0 && b <= a && b > -a)
    {
        return 4*a*a + a + b;
    }
    // Only a=0, b=0 is not in a zone
    else
    {
        return 0;
    }
}

double distance2d(Point p1, Point p2)
{
    return distanceFormula(p1.x, p1.z, p2.x, p2.z);
}

double distanceFormula(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

double distance3d(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
                (p1.y - p2.y)*(p1.y - p2.y) +
                (p1.z - p2.z)*(p1.z - p2.z));
}

bool isAboveLineXZPlane(Point p, double m, double b)
{
    return p.z < m*p.x + b; // Reverse inequality because up is negative z
}

std::vector<int> getChunkIDsAroundPoint(Point2D p, int radius)
{
    std::vector<int> result;

    // Start at the bottom of the diamond and work up from there
    for(int b = p.z + radius; b >= p.z - radius; b--)
    {
        int distanceFromZ = abs(b - p.z);
        for(int a = p.x - (radius - distanceFromZ); a <= p.x + (radius - distanceFromZ); a++)
        {
            result.push_back(point2DtoChunkID({a,b}));
        }
    }
    return result;
}

std::vector<Point2D> getChunkTopLeftCornersAroundPoint(Point2D p, int radius)
{
    std::vector<Point2D> result;

    // Start at the bottom of the diamond and work up from there
    for(int b = p.z + radius; b >= p.z - radius; b--)
    {
        int distanceFromZ = abs(b - p.z);
        for(int a = p.x - (radius - distanceFromZ); a <= p.x + (radius - distanceFromZ); a++)
        {
            result.push_back({a,b});
        }
    }
    return result;
}

std::vector<int> getChunkIDsAroundPoint(int chunkID, int radius)
{
    return getChunkIDsAroundPoint(chunkIDtoPoint2D(chunkID), radius);
}
std::vector<Point2D> getChunkTopLeftCornersAroundPoint(int chunkID, int radius)
{
    return getChunkTopLeftCornersAroundPoint(chunkIDtoPoint2D(chunkID), radius);
}

int getChunkIDContainingPoint(Point p, int chunkSize)
{
    int x = floor(p.x / chunkSize);
    int z = floor(p.z / chunkSize);
    return point2DtoChunkID({x, z});
}

void movePoint(Point &p, double deltaX, double deltaY, double deltaZ)
{
    p.x += deltaX;
    p.y += deltaY;
    p.z += deltaZ;
}

void rotatePointAroundPoint(Point &p, const Point &pBase, double thetaX, double thetaY, double thetaZ)
{
    // Store the previous coordinates during calculations
    double prevX = 0, prevY = 0, prevZ = 0;

    // Translate pBase to the origin by moving p
    p.x -= pBase.x;
    p.y -= pBase.y;
    p.z -= pBase.z;

    // Rotate around x-axis
    prevY = p.y;
    prevZ = p.z;
    p.y = prevY * cos(thetaX) - prevZ * sin(thetaX);
    p.z = prevY * sin(thetaX) + prevZ * cos(thetaX);

    // Rotate around y-axis
    prevX = p.x;
    prevZ = p.z;
    p.x = prevX * cos(thetaY) - prevZ * sin(thetaY);
    p.z = prevX * sin(thetaY) + prevZ * cos(thetaY);

    // Rotate around z-axis
    prevX = p.x;
    prevY = p.y;
    p.x = prevX * cos(thetaZ) - prevY * sin(thetaZ);
    p.y = prevX * sin(thetaZ) + prevY * cos(thetaZ);

    // Translate back
    p.x += pBase.x;
    p.y += pBase.y;
    p.z += pBase.z;
}

Point getRotatedPointAroundPoint(const Point &p, const Point &pBase, double thetaX, double thetaY, double thetaZ)
{
    Point result = {p.x, p.y, p.z};
    rotatePointAroundPoint(result, pBase, thetaX, thetaY, thetaZ);
    return result;
}

double trueAngleDifference(double angle1, double angle2)
{
    double theta = angle1 - angle2;
    while(theta < 0)
    {
        theta += 2*PI;
    }
    if(theta > PI)
    {
        return 2*PI - theta;
    }
    return theta;

}
bool isInFieldOfView(Point target, Point location, double xzAngle, double yAngle, double fov)
{
    double angleDifXZ = atan2(target.z - location.z, target.x - location.x);
    double angleDifY = atan2(target.y - location.y, distance2d(location, target));
    return trueAngleDifference(angleDifXZ, xzAngle) < fov && trueAngleDifference(angleDifY, yAngle) < fov;
}
double determineLightIntensityAt(Point target, LightSource source, double fadeFactor)
{
    double d = distance3d(target, source.location);
    if(d == 0)
    {
        return source.intensity;
    }
    return source.intensity / (d*d * fadeFactor);
}
double determineLightLevelAt(Point target, LightSource source, double fadeFactor)
{
    if(!isInFieldOfView(target, source.location, source.xzAngle, source.yAngle, source.fieldOfView))
    {
        return 0;
    }
    else
    {
        return determineLightIntensityAt(target, source, fadeFactor);
    }
}

/*
 * + - - - - - +
 * |  \  1  /  |
 * | 4   X   2 |
 * |  /  3  \  |
 * + - - - - - +
 */
std::experimental::optional<Point> correctAlignedRectangularCrossSection(Point p, int buffer, Point c,
                                                                         double xw, double zw)
{
    // Determine which of the 4 zones of the rectangle p lies in
    // Let line 1 have the negative slope, and line 2 have the positive slope
    // Line 1: z = -mx + b1
    // Line 2: z = mx + b2
    double m = zw / xw;
    double b1 = c.z + m*c.x;
    double b2 = c.z - m*c.x;
    bool above1 = isAboveLineXZPlane(p, -m, b1);
    bool above2 = isAboveLineXZPlane(p, m, b2);
    if(above1 && above2) // zone 1
    {
        if(p.z > c.z - zw/2 - buffer)
        {
            return std::experimental::optional<Point>({p.x, p.y, c.z - zw/2 - buffer});
        }
    }
    else if(above1) // zone 4
    {
        if(p.x > c.x - xw/2 - buffer)
        {
            return std::experimental::optional<Point>({c.x - xw/2 - buffer, p.y, p.z});
        }
    }
    else if(above2) // zone 2
    {
        if(p.x < c.x + xw/2 + buffer)
        {
            return std::experimental::optional<Point>({c.x + xw/2 + buffer, p.y, p.z});
        }
    }
    else // zone 3
    {
        if(p.z < c.z + zw/2 + buffer)
        {
            return std::experimental::optional<Point>({p.x, p.y, c.z + zw/2 + buffer});
        }
    }
    return std::experimental::nullopt;
}


std::experimental::optional<Point> correctRectangularCrossSection(Point p, int buffer, Point c,
                                                                  double xw, double zw, double xzAngle)
{
    Point rotatedPoint = getRotatedPointAroundPoint(p, c, 0, -xzAngle, 0);
    std::experimental::optional<Point> correctedPoint = correctAlignedRectangularCrossSection(rotatedPoint, buffer, c, xw, zw);
    if(correctedPoint)
    {
        return getRotatedPointAroundPoint(*correctedPoint, c, 0, xzAngle, 0);
    }
    return correctedPoint;
}

std::experimental::optional<Point> correctAlignedRectangularPrism(Point p, int buffer, Point c,
                                                                         double xw, double yw, double zw)
{
    double distanceOutsideLeftEdge = c.x - xw/2 - p.x;
    double distanceOutsideRightEdge = p.x - c.x - xw/2;
    double distanceAboveTopEdge = p.y - c.y - yw/2;
    double distanceBelowBottomEdge = c.y - yw/2 - p.y;
    double distanceOutsideFrontEdge = p.z - c.z - zw/2;
    double distanceOutsideBackEdge = c.z - zw/2 - p.z;
    // If the point is closest to the top face
    if(distanceAboveTopEdge > distanceOutsideLeftEdge && distanceAboveTopEdge > distanceOutsideRightEdge &&
       distanceAboveTopEdge > distanceOutsideFrontEdge && distanceAboveTopEdge > distanceOutsideBackEdge)
    {
        if(distanceAboveTopEdge >= buffer)
        {
            return std::experimental::nullopt;
        }
        else
        {
            return std::experimental::optional<Point>({p.x, c.y + yw/2 + buffer, p.z});
        }
    }
        // If the point is closest to the bottom face
    else if(distanceBelowBottomEdge > distanceOutsideLeftEdge && distanceBelowBottomEdge > distanceOutsideRightEdge &&
            distanceBelowBottomEdge > distanceOutsideFrontEdge && distanceBelowBottomEdge > distanceOutsideBackEdge)
    {
        if(distanceBelowBottomEdge >= buffer)
        {
            return std::experimental::nullopt;
        }
        else
        {
            return std::experimental::optional<Point>({p.x, c.y - yw/2 - buffer, p.z});
        }
    }
        // Otherwise, assume it is near a side face and correct that
    else
    {
        return correctAlignedRectangularCrossSection(p, buffer, c, xw, zw);
    }
}

std::experimental::optional<Point> correctRectangularPrism(Point p, int buffer, Point c,
                                                           double xw, double yw, double zw, double xzAngle)
{
    Point rotatedPoint = getRotatedPointAroundPoint(p, c, 0, -xzAngle, 0);
    std::experimental::optional<Point> correctedPoint = correctAlignedRectangularPrism(rotatedPoint, buffer, c, xw, yw, zw);
    if(correctedPoint)
    {
        return getRotatedPointAroundPoint(*correctedPoint, c, 0, xzAngle, 0);
    }
    return correctedPoint;
}
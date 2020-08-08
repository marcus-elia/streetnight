#ifndef FPS_TEMPLATE_STRUCTS_H
#define FPS_TEMPLATE_STRUCTS_H

#include <memory>

// This file contains some structs to make
// including simpler


// int points used for the chunks
// in the xz plane
struct Point2D
{
    int x;
    int z;
    bool operator ==(const Point2D& p1)
    {
        return x == p1.x && z == p1.z;
    }
    bool operator !=(const Point2D& p1)
    {
        return x != p1.x || z != p1.z;
    }
};


struct Point
{
    double x;
    double y;
    double z;
};

struct RGBAcolor
{
    double r;
    double g;
    double b;
    double a;
};

struct LightSource
{
    std::shared_ptr<Point> location;
    std::shared_ptr<double> xzAngle;
    std::shared_ptr<double> yAngle;
    double fieldOfView;
    int intensity;
};
#endif //FPS_TEMPLATE_STRUCTS_H

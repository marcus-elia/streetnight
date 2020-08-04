#ifndef STREETNIGHT_DARKNESS_H
#define STREETNIGHT_DARKNESS_H

#include "structs.h"
#include "graphics.h"
#include "mathHelper.h"
#include <vector>

class Darkness
{
private:
    Point playerLoc;
    Point playerLook;
    // A frustum shape
    double depth, nearWidth, nearHeight, farWidth, farHeight;
    double xzAngle, yAngle;
    RGBAcolor color;
    std::vector<Point> corners;
public:
    Darkness();
    Darkness(Point inputPlayerLoc, Point inputPlayerLook, double inputDepth, double inputNearWidth,
            double inputNearHeight, double inputFarWidth, double inputFarHeight, RGBAcolor inputColor);

    void initializeCorners();

    void move(double deltaX, double deltaY, double deltaZ);
    void rotate(double thetaX, double thetaY, double thetaZ);
    // Make xzAngle and yAngle consistent with the current playerLoc and playerLook
    void updateAngles();
    // Directly put in a new playerLoc and playerLook
    void updateCorners(Point newPlayerLoc, Point newPlayerLook);

    void draw() const;
};

#endif //STREETNIGHT_DARKNESS_H

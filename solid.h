#ifndef STREETNIGHT_SOLID_H
#define STREETNIGHT_SOLID_H

#include "structs.h"
#include "mathHelper.h"
#include "graphics.h"
#include <vector>
#include <experimental/optional>
#include <cmath>

// How many lines are drawn on the solid
enum linesDrawnEnum {NoLines, Normal, Low, Medium, High};

class Solid
{
protected:
    Point center;
    double xzAngle;
    RGBAcolor color;
    std::vector<Point> corners;
    double xWidth;
    double yWidth;
    double zWidth;
    RGBAcolor lineColor;
    linesDrawnEnum linesDrawn;

    // When drawing lines on a plane, move the line a little in front of the plane so it shows up
    constexpr const static double lineOffset = 0.5;
public:
    // Constructors
    Solid();
    Solid(Point inputCenter, RGBAcolor inputColor,
          double inputXWidth, double inputYWidth, double inputZWidth, RGBAcolor inputLineColor,
          linesDrawnEnum inputLinesDrawn=Normal);

    // Initialization
    virtual void initializeCorners();

    // Getters
    Point getCenter() const;
    RGBAcolor getColor() const;
    std::vector<Point> getCorners() const;
    double getXWidth() const;
    double getYWidth() const;
    double getZWidth() const;
    double getXZAngle() const;
    RGBAcolor getLineColor() const;

    // Setter
    void setCenter(Point inputCenter);
    void setColor(RGBAcolor inputColor);
    void setCorners(std::vector<Point> inputCorners);
    void setXWidth(double inputXWidth);
    void setYWidth(double inputYWidth);
    void setZWidth(double inputZWidth);
    void setLineColor(RGBAcolor inputLineColor);
    void setXZAngle(double inputAngle); // doesn't rotate the corners, just sets the angle


    // Moving
    void move(double deltaX, double deltaY, double deltaZ);
    void rotate(double thetaX, double thetaY, double thetaZ);
    void rotateAroundPoint(const Point &ownerCenter, double thetaX, double thetaY, double thetaZ);

    virtual void draw(double lightLevel) const = 0;
};

#endif //STREETNIGHT_SOLID_H

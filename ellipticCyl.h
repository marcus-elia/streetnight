#ifndef STREETNIGHT_ELLIPTICCYL_H
#define STREETNIGHT_ELLIPTICCYL_H

#include "solid.h"

class EllipticCyl : public Solid
{
private:
    const static int smoothness = 24;
    double topXWidth;
    double topZWidth;

    const static int distanceBetweenHighLines = 8;
    const static int distanceBetweenMediumLines = 32;
    const static int distanceBetweenLowLines = 56;

    std::vector<std::vector<Point>> linePoints;
public:
    EllipticCyl();
    EllipticCyl(Point inputCenter, RGBAcolor inputColor,
    double inputXWidth, double inputYWidth, double inputZWidth, RGBAcolor inputLineColor,
    linesDrawnEnum inputLinesDrawn=Normal);
    EllipticCyl(Point inputCenter, RGBAcolor inputColor,
    double inputXWidth, double inputYWidth, double inputZWidth, RGBAcolor inputLineColor,
    double inputTopXWidth, double inputTopZWidth,
    linesDrawnEnum inputLinesDrawn=Normal);

    // Make the corners, which in this case are the points along the circumference of the
    // top and bottom ellipses (the 2i th entry is a top point, and the 2i+1 th entry is the
    // bottom point corresponding to it).
    void initializeCorners();

    // Make points for drawing gridlines, if applicable
    void initializeLinePoints();

    // Getters
    double getTopXWidth() const;
    double getTopZWidth() const;

    // Geometry
    // Returns the x or z radius at a height of y above the base
    double getXRadiusAtHeight(double y) const;
    double getZRadiusAtHeight(double y) const;
    // Get the coordinates on circumference at given height and angle
    Point getPointAtHeight(double y, double theta) const;

    void draw(double lightLevel) const;
    void drawLines(double lightLevel) const;
    void drawFaces(double lightLevel) const;
    void drawGridLines(double lightLevel) const;
};

#endif //STREETNIGHT_ELLIPTICCYL_H

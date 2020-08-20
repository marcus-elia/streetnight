#ifndef STREETNIGHT_FRUSTUM_H
#define STREETNIGHT_FRUSTUM_H

#include "solid.h"

class Frustum : public Solid
{
private:
    double upperXWidth;
    double upperZWidth;

    const static int distanceBetweenHighLines = 8;
    const static int distanceBetweenMediumLines = 16;
    const static int distanceBetweenLowLines = 24;
    // Points for drawing extra gridlines on the faces
    std::vector<Point> xLinePoints;
    std::vector<Point> yLinePoints;
    std::vector<Point> zLinePoints;
public:
    Frustum();

    Frustum(Point inputCenter, RGBAcolor inputColor,
            double inputXWidth, double inputYWidth, double inputZWidth, RGBAcolor inputLineColor,
            double inputUpperXWidth, double inputUpperZWidth,
            linesDrawnEnum inputLinesDrawn=Normal);

    void initializeCorners();
    // Make points for drawing gridlines, if applicable
    void initializeLinePoints();
    void initializeXLinePoints();
    void initializeYLinePoints();
    void initializeZLinePoints();

    // Geometry
    // Returns the x or z width at a height of y above the base
    double getXWidthAtHeight(double y) const;
    double getZWidthAtHeight(double y) const;

    void draw(double lightLevel) const;
    void drawLines(double lightLevel) const;
    void drawFaces(double lightLevel) const;
    void drawGridLines(double lightLevel) const;
};

#endif //STREETNIGHT_FRUSTUM_H

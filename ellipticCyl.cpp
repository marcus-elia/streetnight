#include "ellipticCyl.h"

EllipticCyl::EllipticCyl() : Solid()
{
    topXWidth = xWidth;
    topZWidth = zWidth;
    initializeCorners();
    initializeLinePoints();
}
EllipticCyl::EllipticCyl(Point inputCenter, RGBAcolor inputColor,
                   double inputXWidth, double inputYWidth, double inputZWidth, RGBAcolor inputLineColor,
                   linesDrawnEnum inputLinesDrawn) :
        Solid(inputCenter, inputColor, inputXWidth, inputYWidth, inputZWidth, inputLineColor, inputLinesDrawn)
{
    topXWidth = xWidth;
    topZWidth = zWidth;
    initializeCorners();
    initializeLinePoints();
}
EllipticCyl::EllipticCyl(Point inputCenter, RGBAcolor inputColor,
            double inputXWidth, double inputYWidth, double inputZWidth, RGBAcolor inputLineColor,
            double inputTopXWidth, double inputTopZWidth,
            linesDrawnEnum inputLinesDrawn) :
        Solid(inputCenter, inputColor, inputXWidth, inputYWidth, inputZWidth, inputLineColor, inputLinesDrawn)
{
    topXWidth = inputTopXWidth;
    topZWidth = inputTopZWidth;
    initializeCorners();
    initializeLinePoints();
}

void EllipticCyl::initializeCorners()
{
    double x, z, xTop, zTop;
    for(int i = 0; i < smoothness; i++)
    {
        x = xWidth/2 * cos(2*PI* i / smoothness);
        z = zWidth/2 * sin(2*PI* i / smoothness);
        xTop = topXWidth/2 * cos(2*PI* i / smoothness);
        zTop = topZWidth/2 * sin(2*PI* i / smoothness);
        corners.push_back({center.x + xTop, center.y + yWidth/2, center.z + zTop}); // upper face
        corners.push_back({center.x + x, center.y - yWidth/2, center.z + z}); // lower face
    }
}

void EllipticCyl::initializeLinePoints()
{
    int numPoints;
    double x,y,z;

    // Decide how far apart to make the lines
    if(linesDrawn == Low)
    {
        numPoints = floor(yWidth / distanceBetweenLowLines);
    }
    else if(linesDrawn == Medium)
    {
        numPoints = floor(yWidth / distanceBetweenMediumLines);
    }
    else if(linesDrawn == High)
    {
        numPoints = floor(yWidth / distanceBetweenHighLines);
    }
    else // If linesDrawn = Normal or NoLines, do not add any gridlines on the planes
    {
        return;
    }

    double distanceBetweenPoints = yWidth / numPoints;

    // Iterate through the bottom of the ellipse and add points above it
    for(int i = 1; i < corners.size(); i += 2)
    {
        y = 0;

        double theta = 2*PI* (i+1)/2 / smoothness;

        linePoints.emplace_back();
        for(int j = 0; j < numPoints - 1; j++)
        {
            y += distanceBetweenPoints;
            linePoints.back().push_back(getPointAtHeight(y, theta));
        }
    }
}


// =============================
//
//           Geometry
//
// =============================

double EllipticCyl::getXRadiusAtHeight(double y) const
{
    double slope = (topXWidth - xWidth) / 2 / yWidth;
    return xWidth/2 + slope*y;
}

double EllipticCyl::getZRadiusAtHeight(double y) const
{
    double slope = (topZWidth - zWidth) / 2 / yWidth;
    return zWidth/2 + slope*y;
}

Point EllipticCyl::getPointAtHeight(double y, double theta) const
{
    double xRad = getXRadiusAtHeight(y);
    double zRad = getZRadiusAtHeight(y);
    return {center.x + xRad*cos(theta), center.y - yWidth/2 + y, center.z + zRad*sin(theta)};
}

void EllipticCyl::draw(double lightLevel) const
{
    drawLines(lightLevel);
    drawFaces(lightLevel);
}

void EllipticCyl::drawLines(double lightLevel) const
{
    if(linesDrawn == NoLines)
    {
        return;
    }

    setGLColorLightLevel(lineColor, lightLevel);
    glBegin(GL_LINES);
    for(int i = 0; i < 2*smoothness - 3; i += 2)
    {
        // Upper face
        drawPoint(corners[i]);
        drawPoint(corners[i + 2]);

        // Lower face
        drawPoint(corners[i + 1]);
        drawPoint(corners[i + 3]);

        // Verticals
        if(((linesDrawn == Low || linesDrawn == Normal) && i % 12 == 0) || (linesDrawn == Medium && i % 6 == 0) ||
           linesDrawn == High)
        {
            drawPoint(corners[i]);
            drawPoint(corners[i+1]);
        }
    }
    // Connect the end to the start
    drawPoint(corners[2*smoothness-2]);
    drawPoint(corners[0]);
    drawPoint(corners[2*smoothness-1]);
    drawPoint(corners[1]);

    // Vertical
    if(linesDrawn == High)
    {
        drawPoint(corners[2*smoothness-2]);
        drawPoint(corners[2*smoothness-1]);
    }

    glEnd();

    if(linesDrawn != Normal)
    {
        drawGridLines(lightLevel);
    }
}

void EllipticCyl::drawFaces(double lightLevel) const
{
    setGLColorLightLevel(color, lightLevel);
    glDisable(GL_CULL_FACE);

    // Draw the top and bottom circles
    glBegin(GL_TRIANGLE_FAN);
    // center
    drawPoint({center.x, center.y + yWidth/2, center.z});
    // top circumference
    for(int i = 0; i < smoothness; i++)
    {
        drawPoint(corners[2*i]);
    }
    drawPoint(corners[0]);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    // center
    drawPoint({center.x, center.y - yWidth/2, center.z});
    // bottom circumference
    for(int i = 0; i < smoothness; i++)
    {
        drawPoint(corners[2*i + 1]);
    }
    drawPoint(corners[1]);
    glEnd();

    // Draw the cylinder part

    glBegin(GL_TRIANGLE_STRIP);

    for(int i = 0; i < 2*smoothness; i++)
    {
        drawPoint(corners[i]);
    }
    // Connect the end to the start
    drawPoint(corners[0]);
    drawPoint(corners[1]);
    glEnd();

    glEnable(GL_CULL_FACE);
}

void EllipticCyl::drawGridLines(double lightLevel) const
{
    setGLColorLightLevel(lineColor, lightLevel);
    glBegin(GL_LINES);

    int pointsPerSide;

    pointsPerSide = linePoints[0].size();
    for(int i = 0; i < pointsPerSide; i++)
    {
        drawPoint(linePoints[0][i]);
        for(int j = 1; j < smoothness; j++)
        {
            drawPoint(linePoints[j][i]);
            drawPoint(linePoints[j][i]);
        }
        drawPoint(linePoints[0][i]);
    }

    glEnd();
}
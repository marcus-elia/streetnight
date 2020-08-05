#include "darkness.h"

Darkness::Darkness()
{
    playerLoc = {0, 10, 0};
    playerLook = {0, 10, -10};
    depth = 300;
    nearWidth = 100;
    nearHeight = 100;
    farWidth = 400;
    farHeight = 400;
    color = {0,0,0,1};
    initializeCorners();
}
Darkness::Darkness(Point inputPlayerLoc, Point inputPlayerLook, double inputDepth, double inputNearWidth,
double inputNearHeight, double inputFarWidth, double inputFarHeight, RGBAcolor inputColor)
{
    playerLoc = inputPlayerLoc;
    playerLook = inputPlayerLook;
    depth = inputDepth;
    nearWidth = inputNearWidth;
    nearHeight = inputNearHeight;
    farWidth = inputFarWidth;
    farHeight = inputFarHeight;
    color = inputColor;
    initializeCorners();
}

void Darkness::initializeCorners()
{
    // Initially facing the negative z direction

    // The near face, cw from top left
    corners.push_back({playerLoc.x - nearWidth/2, playerLoc.y - nearHeight/2, playerLoc.z});
    corners.push_back({playerLoc.x + nearWidth/2, playerLoc.y - nearHeight/2, playerLoc.z});
    corners.push_back({playerLoc.x + nearWidth/2, playerLoc.y + nearHeight/2, playerLoc.z});
    corners.push_back({playerLoc.x - nearWidth/2, playerLoc.y + nearHeight/2, playerLoc.z});
    // The far face, cw from top left
    corners.push_back({playerLoc.x - farWidth/2, playerLoc.y - farHeight/2, playerLoc.z - depth});
    corners.push_back({playerLoc.x + farWidth/2, playerLoc.y - farHeight/2, playerLoc.z - depth});
    corners.push_back({playerLoc.x + farWidth/2, playerLoc.y + farHeight/2, playerLoc.z - depth});
    corners.push_back({playerLoc.x - farWidth/2, playerLoc.y + farHeight/2, playerLoc.z - depth});
}

void Darkness::move(double deltaX, double deltaY, double deltaZ)
{
    for(Point &p : corners)
    {
        movePoint(p, deltaX, deltaY, deltaZ);
    }
    movePoint(playerLoc, deltaX, deltaY, deltaZ);
    movePoint(playerLook, deltaX, deltaY, deltaZ);
}
void Darkness::rotate(double thetaX, double thetaY, double thetaZ)
{
    for(Point &p : corners)
    {
        rotatePointAroundPoint(p, playerLoc, thetaX, thetaY, thetaZ);
    }
    rotatePointAroundPoint(playerLook, playerLoc, thetaX, thetaY, thetaZ);
    updateAngles();
}
void Darkness::updateAngles()
{
    xzAngle = atan2(playerLook.z - playerLoc.z, playerLook.x - playerLoc.x);
    yAngle = atan2(playerLook.y - playerLoc.y, distance2d(playerLoc, playerLook));
}
void Darkness::updateCorners(Point newPlayerLoc, Point newPlayerLook)
{
    double deltaX = newPlayerLoc.x - playerLoc.x;
    double deltaY = newPlayerLoc.y - playerLoc.y;
    double deltaZ = newPlayerLoc.z - playerLoc.z;
    move(deltaX, deltaY, deltaZ);
}

void Darkness::draw() const
{
    setGLColor(color);
    glBegin(GL_QUADS);
    // Left face
    drawPoint(corners[0]);
    drawPoint(corners[3]);
    drawPoint(corners[4]);
    drawPoint(corners[7]);
    // Right Face
    setGLColor({1,0,0,1});
    drawPoint(corners[5]);
    drawPoint(corners[1]);
    drawPoint(corners[2]);
    drawPoint(corners[6]);
    // Back face
    setGLColor({1,1,0,1});
    drawPoint(corners[4]);
    drawPoint(corners[5]);
    drawPoint(corners[6]);
    drawPoint(corners[7]);
    // Top face
    drawPoint(corners[4]);
    drawPoint(corners[0]);
    drawPoint(corners[1]);
    drawPoint(corners[5]);
    glEnd();
}
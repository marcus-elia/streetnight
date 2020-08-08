#include "chunk.h"

Chunk::Chunk()
{
    topLeft = {0, 0};
    sideLength = 512;
    groundColor = {1,1,1,1};
    initializeCenter();
    initializeChunkID();
    initializeShapes();
}
Chunk::Chunk(Point2D inputTopLeft, int inputSideLength, RGBAcolor inputGroundColor)
{
    topLeft = inputTopLeft;
    sideLength = inputSideLength;
    groundColor = inputGroundColor;
    initializeCenter();
    initializeChunkID();
    initializeShapes();
}

void Chunk::initializeCenter()
{
    center = {sideLength*topLeft.x + sideLength/2.0, 0,sideLength*topLeft.z + sideLength/2.0};
}
void Chunk::initializeChunkID()
{
    chunkID = point2DtoChunkID(topLeft);
}
void Chunk::initializeShapes()
{
    double x, z;
    double height, width;
    for(int i = 0; i < 2; i++)
    {
        x = center.x + sideLength/2 - (rand() % sideLength);
        z = center.z + sideLength/2 - (rand() % sideLength);
        height = 50 + (rand() % 200);
        width = 15 + (rand() % 10);
        Point location = {x, height/2, z};
        RGBAcolor shapeColor = {(rand() % 100)/100.0, (rand() % 100)/100.0, (rand() % 100)/100.0, 1.0};
        shapes.push_back(std::make_shared<RecPrism>(RecPrism(location, shapeColor, width, height, width, {1,1,1,1})));
    }
}

// Getters
Point2D Chunk::getTopLeft() const
{
    return topLeft;
}
int Chunk::getSideLength() const
{
    return sideLength;
}
Point Chunk::getCenter() const
{
    return center;
}
int Chunk::getChunkID()
{
    return chunkID;
}

void Chunk::draw(double lightLevel) const
{
    setGLColorLightLevel(groundColor, lightLevel);
    glBegin(GL_QUADS);
    glVertex3f(center.x - sideLength/2, 0, center.z - sideLength/2);
    glVertex3f(center.x - sideLength/2, 0, center.z + sideLength/2);
    glVertex3f(center.x + sideLength/2, 0, center.z + sideLength/2);
    glVertex3f(center.x + sideLength/2, 0, center.z - sideLength/2);
    glEnd();

    for(std::shared_ptr<Solid> s : shapes)
    {
        s->draw(lightLevel);
    }
}
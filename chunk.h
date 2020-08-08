#ifndef FPS_TEMPLATE_CHUNK_H
#define FPS_TEMPLATE_CHUNK_H

#include <experimental/optional>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "graphics.h"
#include "structs.h"
#include "mathHelper.h"
#include "recPrism.h"

class Chunk
{
private:
    // The top left coordinate divided by sideLength
    // So if sideLength = 512, then (3,2) describes the
    // chunk whose top left corner is (1536, 1024)
    Point2D topLeft;
    int sideLength;

    Point center;   // The actual center (y-coordinate = 0)

    // The number of the chunk based on its location
    int chunkID;

    RGBAcolor groundColor;

    // Temporary
    std::vector<std::shared_ptr<Solid>> shapes;

public:
    Chunk();
    Chunk(Point2D inputTopLeft, int inputSideLength, RGBAcolor inputGroundColor);

    void initializeCenter();
    void initializeChunkID();
    // Temporary
    void initializeShapes();

    // Getters
    Point2D getTopLeft() const;
    int getSideLength() const;
    Point getCenter() const;
    int getChunkID();

    void draw(double lightLevel) const;
};
#endif //FPS_TEMPLATE_CHUNK_H

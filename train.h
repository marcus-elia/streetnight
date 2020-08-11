#ifndef STREETNIGHT_TRAIN_H
#define STREETNIGHT_TRAIN_H

#include "recPrism.h"
#include <vector>
#include <memory>

class Train
{
private:
    Point location;
    RGBAcolor color;
    double xWidth, yWidth, zWidth;
    double speed;
    Point velocity;
    double xzAngle;
    std::vector<std::shared_ptr<Solid>> solids;
public:
    Train();
    Train(Point inputLocation, RGBAcolor inputColor, double inputXWidth, double inputYWidth, double inputZWidth,
            double inputSpeed, double inputXZAngle);

    void initializeVelocity();
    void initializeSolids();

    // Getters
    Point getLocation() const;
    Point getVelocity() const;

    void draw(double lightLevel) const;
    void tick();
    void move();
};

#endif //STREETNIGHT_TRAIN_H

#ifndef STREETNIGHT_TRAIN_H
#define STREETNIGHT_TRAIN_H

#include "recPrism.h"
#include "ellipticCyl.h"
#include "mathHelper.h"
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
    RecPrism hitbox;
public:
    Train();
    Train(Point inputLocation, RGBAcolor inputColor, double inputXWidth, double inputYWidth, double inputZWidth,
            double inputSpeed, double inputXZAngle);

    void initializeVelocity();
    void initializeSolids();
    void initializeHitbox();

    // Getters
    Point getLocation() const;
    Point getVelocity() const;

    void draw(double lightLevel) const;
    void tick();
    void move();

    std::experimental::optional<Point> correctCollision(Point p, double buffer) const;
};

#endif //STREETNIGHT_TRAIN_H

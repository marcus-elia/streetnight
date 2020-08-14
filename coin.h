#ifndef STREETNIGHT_COIN_H
#define STREETNIGHT_COIN_H

#include "recPrism.h"

class Coin
{
private:
    Point location;
    double radius;
    double thickness;
    double xzAngle;
    double rotationSpeed;
    RGBAcolor color;
    std::vector<std::shared_ptr<Solid>> solids;
    RecPrism hitbox;
public:
    Coin();
    Coin(Point inputLocation, double inputRadius, double inputThickness, double inputRotationSpeed,
            RGBAcolor inputColor);

    void initializeSolids();
    void initializeHitbox();

    // Getters
    Point getLocation() const;
    double getRadius() const;
    double getThickness() const;
    double getXZAngle() const;

    void setXZAngle(double inputAngle);
    void move(double deltaX, double deltaY, double deltaZ);

    void draw(double lightLevel) const;
    void tick();

    bool hasCollision(Point p, double buffer) const;
};

#endif //STREETNIGHT_COIN_H

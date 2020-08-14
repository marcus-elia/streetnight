#include "coin.h"

Coin::Coin()
{
    location = {0, 25, 0};
    radius = 10;
    thickness = 8;
    rotationSpeed = 0.1;
    color = {1.0, 0.8, 0.1, 1.0};
    initializeSolids();
    initializeHitbox();
}
Coin::Coin(Point inputLocation, double inputRadius, double inputThickness, double inputRotationSpeed,
        RGBAcolor inputColor)
{
    location = inputLocation;
    radius = inputRadius;
    thickness = inputThickness;
    rotationSpeed = inputRotationSpeed;
    color = inputColor;
    initializeSolids();
    initializeHitbox();
}

void Coin::initializeSolids()
{
    std::shared_ptr<RecPrism> coinShape = std::make_shared<RecPrism>(RecPrism(location, color, 2*radius, thickness, 2*radius, {1,1,1,1}));
    coinShape->rotate(0, -PI/2, 0);
    solids.push_back(coinShape);
}
void Coin::initializeHitbox()
{
    hitbox = RecPrism(location, {1,0,0,0.5}, 2*radius, 2*radius, thickness, {1,1,1,1});
}

// Getters
Point Coin::getLocation() const
{
    return location;
}
double Coin::getRadius() const
{
    return radius;
}
double Coin::getThickness() const
{
    return thickness;
}
double Coin::getXZAngle() const
{
    return xzAngle;
}

void Coin::setXZAngle(double inputAngle)
{
    if(inputAngle > 2*PI)
    {
        xzAngle = inputAngle - 2*PI;
    }
    else if(inputAngle < 0)
    {
        xzAngle = inputAngle + 2*PI;
    }
    else
    {
        xzAngle = inputAngle;
    }
}

void Coin::draw(double lightLevel) const
{
    for(std::shared_ptr<Solid> s : solids)
    {
        s->draw(lightLevel);
    }
}
void Coin::tick()
{
    for(std::shared_ptr<Solid> s : solids)
    {
        s->rotate(0, rotationSpeed, 0);
    }
    hitbox.rotate(0, rotationSpeed, 0);
}

bool Coin::hasCollision(Point p, double buffer) const
{
    return correctRectangularPrism(p, buffer, hitbox.getCenter(), hitbox.getXWidth(), hitbox.getYWidth(), hitbox.getZWidth(), hitbox.getXZAngle()) != std::experimental::nullopt;
}
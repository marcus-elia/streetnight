#include "train.h"

Train::Train()
{
    location = {0, 30, 100};
    color = {0.0, 0.0, 0.3, 1.0};
    xWidth = 60;
    yWidth = 60;
    zWidth = 120;
    speed = 2.5;
    xzAngle = 3*PI/2;
    initializeVelocity();
    initializeSolids();
    initializeHitbox();
}
Train::Train(Point inputLocation, RGBAcolor inputColor, double inputXWidth, double inputYWidth, double inputZWidth,
double inputSpeed, double inputXZAngle)
{
    location = inputLocation;
    color = inputColor;
    xWidth = inputXWidth;
    yWidth = inputYWidth;
    zWidth = inputZWidth;
    speed = inputSpeed;
    xzAngle = inputXZAngle;
    initializeVelocity();
    initializeSolids();
    initializeHitbox();
}

void Train::initializeVelocity()
{
    velocity.x = cos(xzAngle)*speed;
    velocity.y = 0;
    velocity.z = sin(xzAngle)*speed;
}
void Train::initializeSolids()
{
    // Main tank
    Point center = {location.x, location.y + yWidth/2 - xWidth/2 , location.z - zWidth/8};
    std::shared_ptr<EllipticCyl> mainTank = std::make_shared<EllipticCyl>(EllipticCyl(center, color, xWidth, 3*zWidth/4, xWidth, {1,1,1,1}));
    mainTank->rotate(PI/2, 0, 0);
    mainTank->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(mainTank);

    // Back
    center = {location.x, location.y, location.z + 3*zWidth/8};
    std::shared_ptr<RecPrism> back = std::make_shared<RecPrism>(RecPrism(center, color, xWidth, yWidth, zWidth/4, {1,1,1,1}));
    back->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(back);

    // Base
    center = {location.x, location.y - xWidth/2, location.z};
    std::shared_ptr<RecPrism> base = std::make_shared<RecPrism>(RecPrism(center, color, xWidth, yWidth - xWidth, zWidth, {1,1,1,1}));
    base->rotate(0, xzAngle - 3*PI/2, 0);
    solids.push_back(base);
}
void Train::initializeHitbox()
{
    hitbox = RecPrism(location, {1,0.9,0.9,0.5}, xWidth, yWidth, zWidth, {1,1,1,1});
    hitbox.rotate(0, xzAngle - 3*PI/2, 0);
}

// Getters
Point Train::getLocation() const
{
    return location;
}
Point Train::getVelocity() const
{
    return velocity;
}

void Train::draw(double lightLevel) const
{
    for(std::shared_ptr<Solid> s : solids)
    {
        s->draw(lightLevel);
    }
}
void Train::tick()
{
    move();
}
void Train::move()
{
    location.x += velocity.x;
    location.y += velocity.y;
    location.z += velocity.z;
    for(std::shared_ptr<Solid> s : solids)
    {
        s->move(velocity.x, velocity.y, velocity.z);
    }
    hitbox.move(velocity.x, velocity.y, velocity.z);
}

std::experimental::optional<Point> Train::correctCollision(Point p, double buffer) const
{
    return correctRectangularPrism(p, buffer, hitbox.getCenter(), hitbox.getXWidth(), hitbox.getYWidth(), hitbox.getZWidth(), hitbox.getXZAngle());
}
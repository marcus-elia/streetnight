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
    Point center = {location.x, location.y + yWidth/2 - xWidth/2, location.z - zWidth/8};
    std::shared_ptr<EllipticCyl> mainTank = std::make_shared<EllipticCyl>(EllipticCyl(center, color, xWidth, 3*zWidth/4, xWidth, {1,1,1,1}));
    mainTank->rotate(PI/2, 0, 0);
    mainTank->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(mainTank);

    // Back
    center = {location.x, location.y + yWidth/2 - xWidth/2, location.z + 3*zWidth/8};
    std::shared_ptr<RecPrism> back = std::make_shared<RecPrism>(RecPrism(center, color, xWidth, xWidth, zWidth/4, {1,1,1,1}));
    back->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(back);

    // Roof
    center = {location.x, location.y + yWidth/2, location.z + 3*zWidth/8};
    std::shared_ptr<EllipticCyl> roof = std::make_shared<EllipticCyl>(EllipticCyl(center, color, xWidth, zWidth/4, xWidth/4, {1,1,1,1}, NoLines));
    roof->rotate(PI/2, 0, 0);
    roof->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(roof);

    // Smokestack
    center = {location.x, location.y + yWidth/2, location.z - 3*zWidth/8};
    std::shared_ptr<EllipticCyl> smokestack = std::make_shared<EllipticCyl>(EllipticCyl(center, color, xWidth/4, yWidth/2, xWidth/4, {1,1,1,1}));
    smokestack->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(smokestack);

    // Base
    center = {location.x, location.y - xWidth/2, location.z};
    std::shared_ptr<RecPrism> base = std::make_shared<RecPrism>(RecPrism(center, color, xWidth/2, yWidth - xWidth, zWidth, {1,1,1,1}));
    base->rotate(0, xzAngle - 3*PI/2, 0);
    solids.push_back(base);

    // Front bar
    center = {location.x, location.y - yWidth/4, location.z - zWidth/2};
    std::shared_ptr<RecPrism> frontBar = std::make_shared<RecPrism>(RecPrism(center, {1,0,0,1}, xWidth, yWidth/8, xWidth/8, {1,1,1,1}));
    frontBar->rotateAroundPoint(location,0, xzAngle - 3*PI/2, 0);
    solids.push_back(frontBar);

    // Wheels
    double wheelWidth = xWidth/10;
    double largeDiameter = zWidth/4;
    double smallDiameter = zWidth/8;
    center = {location.x - xWidth/2, location.y - yWidth/2 + largeDiameter/2, location.z + zWidth/2 - largeDiameter/2};
    std::shared_ptr<EllipticCyl> backLeftWheel = std::make_shared<EllipticCyl>(EllipticCyl(center, color, largeDiameter, wheelWidth, largeDiameter, {1,1,1,1}));
    backLeftWheel->rotate(0, 0, PI/2);
    backLeftWheel->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(backLeftWheel);
    center = {location.x + xWidth/2, location.y - yWidth/2 + largeDiameter/2, location.z + zWidth/2 - largeDiameter/2};
    std::shared_ptr<EllipticCyl> backRightWheel = std::make_shared<EllipticCyl>(EllipticCyl(center, color, largeDiameter, wheelWidth, largeDiameter, {1,1,1,1}));
    backRightWheel->rotate(0, 0, PI/2);
    backRightWheel->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(backRightWheel);
    center = {location.x - xWidth/2, location.y - yWidth/2 + largeDiameter/2, location.z + zWidth/2 - 3*largeDiameter/2};
    std::shared_ptr<EllipticCyl> secondBackLeftWheel = std::make_shared<EllipticCyl>(EllipticCyl(center, color, largeDiameter, wheelWidth, largeDiameter, {1,1,1,1}));
    secondBackLeftWheel->rotate(0, 0, PI/2);
    secondBackLeftWheel->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(secondBackLeftWheel);
    center = {location.x + xWidth/2, location.y - yWidth/2 + largeDiameter/2, location.z + zWidth/2 - 3*largeDiameter/2};
    std::shared_ptr<EllipticCyl> secondBackRightWheel = std::make_shared<EllipticCyl>(EllipticCyl(center, color, largeDiameter, wheelWidth, largeDiameter, {1,1,1,1}));
    secondBackRightWheel->rotate(0, 0, PI/2);
    secondBackRightWheel->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(secondBackRightWheel);
    center = {location.x - xWidth/2, location.y - yWidth/2 + largeDiameter/2, location.z + zWidth/2 - 5*largeDiameter/2};
    std::shared_ptr<EllipticCyl> thirdBackLeftWheel = std::make_shared<EllipticCyl>(EllipticCyl(center, color, largeDiameter, wheelWidth, largeDiameter, {1,1,1,1}));
    thirdBackLeftWheel->rotate(0, 0, PI/2);
    thirdBackLeftWheel->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(thirdBackLeftWheel);
    center = {location.x + xWidth/2, location.y - yWidth/2 + largeDiameter/2, location.z + zWidth/2 - 5*largeDiameter/2};
    std::shared_ptr<EllipticCyl> thirdBackRightWheel = std::make_shared<EllipticCyl>(EllipticCyl(center, color, largeDiameter, wheelWidth, largeDiameter, {1,1,1,1}));
    thirdBackRightWheel->rotate(0, 0, PI/2);
    thirdBackRightWheel->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(thirdBackRightWheel);
    center = {location.x - xWidth/2, location.y - yWidth/2 + smallDiameter/2, location.z - zWidth/2 + smallDiameter/2};
    std::shared_ptr<EllipticCyl> frontLeftWheel = std::make_shared<EllipticCyl>(EllipticCyl(center, color, smallDiameter, wheelWidth, smallDiameter, {1,1,1,1}));
    frontLeftWheel->rotate(0, 0, PI/2);
    frontLeftWheel->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(frontLeftWheel);
    center = {location.x + xWidth/2, location.y - yWidth/2 + smallDiameter/2, location.z - zWidth/2 + smallDiameter/2};
    std::shared_ptr<EllipticCyl> frontRightWheel = std::make_shared<EllipticCyl>(EllipticCyl(center, color, smallDiameter, wheelWidth, smallDiameter, {1,1,1,1}));
    frontRightWheel->rotate(0, 0, PI/2);
    frontRightWheel->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(frontRightWheel);
    center = {location.x - xWidth/2, location.y - yWidth/2 + smallDiameter/2, location.z - zWidth/2 + 3*smallDiameter/2};
    std::shared_ptr<EllipticCyl> secondFrontLeftWheel = std::make_shared<EllipticCyl>(EllipticCyl(center, color, smallDiameter, wheelWidth, smallDiameter, {1,1,1,1}));
    secondFrontLeftWheel->rotate(0, 0, PI/2);
    secondFrontLeftWheel->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(secondFrontLeftWheel);
    center = {location.x + xWidth/2, location.y - yWidth/2 + smallDiameter/2, location.z - zWidth/2 + 3*smallDiameter/2};
    std::shared_ptr<EllipticCyl> secondFrontRightWheel = std::make_shared<EllipticCyl>(EllipticCyl(center, color, smallDiameter, wheelWidth, smallDiameter, {1,1,1,1}));
    secondFrontRightWheel->rotate(0, 0, PI/2);
    secondFrontRightWheel->rotateAroundPoint(location, 0, xzAngle - 3*PI/2, 0);
    solids.push_back(secondFrontRightWheel);
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
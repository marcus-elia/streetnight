#include "lampPost.h"

LampPost::LampPost()
{
    location = {0, 15, 0};
    poleRadius = 4;
    poleHeight = 30;
    lightRadius = 5;
    lightHeight = 8;
    poleColor = {0, 0.5, 0.1, 1.0};
    lightColor = {1.0, 1.0, 0.5, 1.0};
    lightIntensity = 8;
    initializeSolids();
}
LampPost::LampPost(Point inputLocation, double inputPoleRadius, double inputPoleHeight, double inputLightRadius,
double inputLightHeight, RGBAcolor inputPoleColor, RGBAcolor inputLightColor, double inputLightIntensity)
{
    location = inputLocation;
    poleRadius = inputPoleRadius;
    poleHeight = inputPoleHeight;
    lightRadius = inputLightRadius;
    lightHeight = inputLightHeight;
    poleColor = inputPoleColor;
    lightColor = inputLightColor;
    lightIntensity = inputLightIntensity;
    initializeSolids();
}

void LampPost::initializeSolids()
{
    solids.push_back(std::make_shared<RecPrism>(RecPrism(location, poleColor, 2*poleRadius, poleHeight, 2*poleRadius, {1,1,1,1})));
    Point center = getLightLocation();
    solids.push_back(std::make_shared<RecPrism>(RecPrism(center, lightColor, 2*lightRadius, lightHeight, 2*lightRadius, {1,1,1,1})));
}

// Getters
Point LampPost::getLocation() const
{
    return location;
};
double LampPost::getLightIntensity() const
{
    return lightIntensity;
};
Point LampPost::getLightLocation() const
{
    return {location.x, location.y + poleHeight/2 + lightHeight/2, location.z};
};

void LampPost::draw(double lightLevel) const
{
    for(std::shared_ptr<Solid> s : solids)
    {
        s->draw(lightLevel);
    }
};
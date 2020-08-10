#ifndef STREETNIGHT_LAMPPOST_H
#define STREETNIGHT_LAMPPOST_H

#include "recPrism.h"
#include <vector>
#include <memory>

class LampPost
{
private:
    Point location; // location.y is halfway up the pole
    double poleRadius;
    double poleHeight;
    double lightRadius;
    double lightHeight;
    RGBAcolor poleColor;
    RGBAcolor lightColor;
    double lightIntensity;
    std::vector<std::shared_ptr<Solid>> solids;
public:
    LampPost();
    LampPost(Point inputLocation, double inputPoleRadius, double inputPoleHeight, double inputLightRadius,
            double inputLightHeight, RGBAcolor inputPoleColor, RGBAcolor inputLightColor, double inputLightIntensity);

    void initializeSolids();

    // Getters
    Point getLocation() const;
    double getLightIntensity() const;
    Point getLightLocation() const;

    void draw(double lightLevel) const;
};

#endif //STREETNIGHT_LAMPPOST_H

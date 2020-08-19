#ifndef FPS_TEMPLATE_MATHHELPER_H
#define FPS_TEMPLATE_MATHHELPER_H

#include "structs.h"
#include <cmath>
#include <vector>
#include <experimental/optional>

// This file contains general math helper functions

const double PI = 3.14159265358979323846;


// Assuming n > 0, this returns the integer closest to n that
// is a perfect square
int nearestPerfectSquare(int n);

// Returns the square root of n, assuming that n is a perfect square
int isqrt(int n);

// Convert between chunkID's and Point2D's
Point2D chunkIDtoPoint2D(int n);
int point2DtoChunkID(Point2D p);

// Euclidean distance
double distanceFormula(double x1, double y1, double x2, double y2);

// Returns the distance in the xz plane, ignoring the y-coordinate
// (calls distanceFormula())
double distance2d(Point p1, Point p2);

double distance3d(Point p1, Point p2);

double xzAngleBetweenPoints(Point base, Point other);

// m and b represent a line such that z = mx + b.
// This determines if p lies above the line in the xz plane
bool isAboveLineXZPlane(Point p, double m, double b);

// Returns the ints corresponding to to all chunks that are within radius of this one,
// using the taxicab metric
std::vector<int> getChunkIDsAroundPoint(Point2D p, int radius);
std::vector<Point2D> getChunkTopLeftCornersAroundPoint(Point2D p, int radius);
// Wrappers
std::vector<int> getChunkIDsAroundPoint(int chunkID, int radius);
std::vector<Point2D> getChunkTopLeftCornersAroundPoint(int chunkID, int radius);

int getChunkIDContainingPoint(Point p, int chunkSize);


// Point operations
void movePoint(Point &p, double deltaX, double deltaY, double deltaZ);
void rotatePointAroundPoint(Point &p, const Point &pBase, double thetaX, double thetaY, double thetaZ);
Point getRotatedPointAroundPoint(const Point &p, const Point &pBase, double thetaX, double thetaY, double thetaZ);

// Light sources
// Return the difference between the two angles, taking into account the fact
// that angles wrap around at 2PI
double trueAngleDifference(double angle1, double angle2);
// Checks if a point is within a given field of view
bool isInFieldOfView(Point target, Point location, double xzAngle, double yAngle, double fov);
// Determines the light intensity based on the distance away
double determineLightIntensityAt(Point target, LightSource source, double fadeFactor);
// Takes into account field of view to determine light level
double determineLightLevelAt(Point target, LightSource source, double fadeFactor);

// Returns the point that the train should aim for if the target moves with a constant
// velocity
Point predictMovement(Point location, double speed, Point targetLocation, Point targetVelocity);

// Working in the xz-plane, assume there is a rectangle centered at c that is aligned with the x,z-axes
// with xw and zw as its dimensions. This returns the Point with adjusted x and z  coordinates to move
// p exactly buffer away from the rectangle.
std::experimental::optional<Point> correctAlignedRectangularCrossSection(Point p, int buffer, Point c,
                                                                         double xw, double zw);

// Performs a rotation and calls correctAlignedRectangularCrossSection(), then unrotates
std::experimental::optional<Point> correctRectangularCrossSection(Point p, int buffer, Point c,
                                                                  double xw, double zw, double xzAngle);

// This assumes x, y, and z are all aligned.
std::experimental::optional<Point> correctAlignedRectangularPrism(Point p, int buffer, Point c,
                                                                         double xw, double yw, double zw);

// This assumes the y-axis is aligned. If there was a y-rotation, this does not work.
std::experimental::optional<Point> correctRectangularPrism(Point p, int buffer, Point c,
                                                                  double xw, double yw, double zw, double xzAngle);

#endif //FPS_TEMPLATE_MATHHELPER_H

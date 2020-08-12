#include "structs.h"
#include "mathHelper.h"
#include <string>
#include <iostream>
#include <vector>

std::string testNearestPerfectSquare();
std::string testISqrt();
std::string testChunkIDtoPoint2D();
std::string testPoint2DtoChunkID();
std::string testDistanceFormula();
std::string testDistance2d();
std::string testGetChunkIDsAroundPoint();
std::string testGetChunkTopLeftCornersAroundPoint();
std::string testGetChunkIDContainingPoint();
std::string testTrueAngleDifference();
std::string testIsInFieldOfView();
std::string testCorrectAlignedRectangularCrossSection();
std::string testCorrectRectangularCrossSection();

int main()
{
    std::string results = "";
    results += testNearestPerfectSquare();
    results += testISqrt();
    results += testChunkIDtoPoint2D();
    results += testPoint2DtoChunkID();
    results += testDistanceFormula();
    results += testDistance2d();
    results += testGetChunkIDsAroundPoint();
    results += testGetChunkTopLeftCornersAroundPoint();
    results += testGetChunkIDContainingPoint();
    results += testTrueAngleDifference();
    results += testIsInFieldOfView();
    results += testCorrectAlignedRectangularCrossSection();
    results += testCorrectRectangularCrossSection();
    std::cout << "\n" << results << std::endl;
    return 0;
}

std::string testNearestPerfectSquare()
{
    std::cout << "\nTesting nearestPerfectSquare()" << std::endl;
    std::string results = "";
    std::vector<int> input {0,1,2,3,4,5,6,7,8,9,10,24,25,26,27,28,29,30,31};
    std::vector<int> exp   {0,1,1,4,4,4,4,9,9,9,9,25,25,25,25,25,25,25,36};

    for(int i = 0; i < input.size(); i++)
    {
        int obs = nearestPerfectSquare(input[i]);
        if(obs != exp[i])
        {
            results += "F";
            std::cout << "Test FAILED on input = " << input[i] << std::endl;
            std::cout << "Expected " << exp[i] << ", got " << obs << std::endl;
        }
        else
        {
            results += ".";
        }
    }

    return results;
}

std::string testISqrt()
{
    std::cout << "\nTesting isqrt()" << std::endl;
    std::string results = "";

    std::vector<int> input {0,1,4,9,16,100};
    std::vector<int> exp   {0,1,2,3,4,10};

    for(int i = 0; i < input.size(); i++)
    {
        int obs = isqrt(input[i]);
        if(obs != exp[i])
        {
            results += "F";
            std::cout << "Test FAILED on input = " << input[i] << std::endl;
            std::cout << "Expected " << exp[i] << ", got " << obs << std::endl;
        }
        else
        {
            results += ".";
        }
    }

    return results;
}

std::string testChunkIDtoPoint2D()
{
    std::cout << "\nTesting chunkIDtoPoint2D()" << std::endl;
    std::string results = "";

    std::vector<int> input;
    std::vector<Point2D> exp;

    input.push_back(0);
    exp.push_back({0,0});
    input.push_back(1);
    exp.push_back({-1,0});
    input.push_back(2);
    exp.push_back({-1,-1});
    input.push_back(3);
    exp.push_back({0,-1});
    input.push_back(4);
    exp.push_back({1,-1});
    input.push_back(5);
    exp.push_back({1,0});
    input.push_back(6);
    exp.push_back({1,1});
    input.push_back(7);
    exp.push_back({0,1});
    input.push_back(8);
    exp.push_back({-1,1});
    input.push_back(9);
    exp.push_back({-2,1});
    input.push_back(10);
    exp.push_back({-2,0});
    input.push_back(11);
    exp.push_back({-2,-1});
    input.push_back(12);
    exp.push_back({-2,-2});
    input.push_back(13);
    exp.push_back({-1,-2});
    input.push_back(14);
    exp.push_back({0,-2});
    input.push_back(35);
    exp.push_back({2,-3});
    input.push_back(49);
    exp.push_back({-4,3});

    for(int i = 0; i < input.size(); i++)
    {
        Point2D obs = chunkIDtoPoint2D(input[i]);
        if(obs != exp[i])
        {
            results += "F";
            std::cout << "Test FAILED on input = " << input[i] << std::endl;
            std::cout << "Expected " << exp[i].x << "," << exp[i].z << ", got " << obs.x << "," << obs.z << std::endl;
        }
        else
        {
            results += ".";
        }
    }

    return results;
}

std::string testPoint2DtoChunkID()
{
    std::cout << "\nTesting point2DtoChunkID()" << std::endl;
    std::string results = "";

    std::vector<Point2D> input;
    std::vector<int> exp;

    input.push_back({0,0});
    exp.push_back(0);
    input.push_back({-1,0});
    exp.push_back(1);
    input.push_back({-1,-1});
    exp.push_back(2);
    input.push_back({0,-1});
    exp.push_back(3);
    input.push_back({1,-1});
    exp.push_back(4);
    input.push_back({1,0});
    exp.push_back(5);
    input.push_back({1,1});
    exp.push_back(6);
    input.push_back({0,1});
    exp.push_back(7);
    input.push_back({-1,1});
    exp.push_back(8);
    input.push_back({-2,1});
    exp.push_back(9);
    input.push_back({-2,0});
    exp.push_back(10);
    input.push_back({-2,-1});
    exp.push_back(11);
    input.push_back({-2,-2});
    exp.push_back(12);
    input.push_back({-1,-2});
    exp.push_back(13);
    input.push_back({0,-2});
    exp.push_back(14);
    input.push_back({2,-3});
    exp.push_back(35);
    input.push_back({-4,3});
    exp.push_back(49);

    for(int i = 0; i < input.size(); i++)
    {
        int obs = point2DtoChunkID(input[i]);
        if(obs != exp[i])
        {
            results += "F";
            std::cout << "Test FAILED on input = " << input[i].x << "," << input[i].z << std::endl;
            std::cout << "Expected " << exp[i]  << ", got " << obs << std::endl;
        }
        else
        {
            results += ".";
        }
    }

    return results;
}

std::string testDistanceFormula()
{
    std::cout << "\nTesting distanceFormula()" << std::endl;
    std::string results = "";

    double x1, z1, x2, z2, exp, obs;
    double tolerance = 0.001;

    // The same point
    x1 = 0, z1 = 0, x2 = 0, z2 = 0;
    exp = 0;
    obs = distanceFormula(x1, z1, x2, z2);
    if(abs(exp - obs) > tolerance)
    {
        results += "F";
        std::cout << "Test FAILED on input = " << x1 << "," << z1 << "," << x2 << "," << z2 << std::endl;
        std::cout << "Expected " << exp  << ", got " << obs << std::endl;
    }
    else
    {
        results += ".";
    }

    // Different points
    x1 = 2, z1 = 2, x2 = -1, z2 = 5.6;
    exp = 4.68614980554399;
    obs = distanceFormula(x1, z1, x2, z2);
    if(abs(exp - obs) > tolerance)
    {
        results += "F";
        std::cout << "Test FAILED on input = " << x1 << "," << z1 << "," << x2 << "," << z2 << std::endl;
        std::cout << "Expected " << exp  << ", got " << obs << std::endl;
    }
    else
    {
        results += ".";
    }

    return results;
}

std::string testDistance2d()
{
    std::cout << "\nTesting distance2d()" << std::endl;
    std::string results = "";

    Point p1, p2;
    double exp, obs;
    double tolerance = 0.001;

    // Different y-value
    p1 = {5, 128, 6};
    p2 = {4, -3, 2};
    exp = 4.123105625617661;
    obs = distance2d(p1, p2);
    if(abs(exp - obs) > tolerance)
    {
        results += "F";
        std::cout << "Test FAILED on different y-coordinate case." << std::endl;
        std::cout << "Expected " << exp  << ", got " << obs << std::endl;
    }
    else
    {
        results += ".";
    }

    p1 = {5, 0, 6};
    p2 = {4, 0, 2};
    exp = 4.123105625617661;
    obs = distance2d(p1, p2);
    if(abs(exp - obs) > tolerance)
    {
        results += "F";
        std::cout << "Test FAILED on same y-coordinate case." << std::endl;
        std::cout << "Expected " << exp  << ", got " << obs << std::endl;
    }
    else
    {
        results += ".";
    }

    return results;
}

std::string testGetChunkIDsAroundPoint()
{
    std::cout << "\nTesting getChunkIDsAroundPoint()" << std::endl;
    std::string results = "";

    Point2D input;
    double radius;
    std::vector<int> exp, obs;

    // Centered at (0,0), radius = 1
    input = {0, 0};
    radius = 1;
    exp = {7,1,0,5,3};
    obs = getChunkIDsAroundPoint(input, radius);
    if(exp.size() != obs.size())
    {
        results += "F";
        std::cout << "Test FAILED when radius = 1" << std::endl;
        std::cout << "Expected vector of size " << exp.size() << ", got size " << obs.size() << std::endl;
    }
    else
    {
        bool passed = true;
        for(int i = 0; i < exp.size(); i++)
        {
            if(exp[i] != obs[i])
            {
                results += "F";
                passed = false;
                std::cout << "Test FAILED when radius = 1" << std::endl;
                std::cout << "Expected entry " << exp[i] << ", got " << obs[i] << std::endl;
                break;
            }
        }
        if(passed)
        {
            results += ".";
        }
    }

    // Centered at (-1,0), radius = 2
    input = {-1, 0};
    radius = 2;
    exp = {23,9,8,7,27,10,1,0,5,11,2,3,13};
    obs = getChunkIDsAroundPoint(input, radius);
    if(exp.size() != obs.size())
    {
        results += "F";
        std::cout << "Test FAILED when radius = 2" << std::endl;
        std::cout << "Expected vector of size " << exp.size() << ", got size " << obs.size() << std::endl;
    }
    else
    {
        bool passed = true;
        for(int i = 0; i < exp.size(); i++)
        {
            if(exp[i] != obs[i])
            {
                results += "F";
                passed = false;
                std::cout << "Test FAILED when radius = 2" << std::endl;
                std::cout << "Expected entry " << exp[i] << ", got " << obs[i] << std::endl;
                break;
            }
        }
        if(passed)
        {
            results += ".";
        }
    }

    return results;
}

std::string testGetChunkTopLeftCornersAroundPoint()
{
    std::cout << "\nTesting getChunkTopLeftCornersAroundPoint()" << std::endl;
    std::string results = "";

    Point2D input;
    double radius;
    std::vector<Point2D> exp, obs;

    // Centered at (0,0), radius = 1
    input = {0, 0};
    radius = 1;
    exp = {{0,1},{-1,0},{0,0},{1,0},{0,-1}};
    obs = getChunkTopLeftCornersAroundPoint(input, radius);
    if(exp.size() != obs.size())
    {
        results += "F";
        std::cout << "Test FAILED when radius = 1" << std::endl;
        std::cout << "Expected vector of size " << exp.size() << ", got size " << obs.size() << std::endl;
    }
    else
    {
        bool passed = true;
        for(int i = 0; i < exp.size(); i++)
        {
            if(exp[i] != obs[i])
            {
                results += "F";
                passed = false;
                std::cout << "Test FAILED when radius = 1" << std::endl;
                std::cout << "Expected entry " << exp[i].x<<","<< exp[i].z<< ", got " <<obs[i].x<<","<<obs[i].z<< std::endl;
                break;
            }
        }
        if(passed)
        {
            results += ".";
        }
    }

    // Centered at (-1,0), radius = 2
    input = {-1, 0};
    radius = 2;
    exp = {{-1,2},{-2,1},{-1,1},{0,1},{-3,0},{-2,0},{-1,0},{0,0},{1,0},{-2,-1},{-1,-1},{0,-1},{-1,-2}};
    obs = getChunkTopLeftCornersAroundPoint(input, radius);
    if(exp.size() != obs.size())
    {
        results += "F";
        std::cout << "Test FAILED when radius = 2" << std::endl;
        std::cout << "Expected vector of size " << exp.size() << ", got size " << obs.size() << std::endl;
    }
    else
    {
        bool passed = true;
        for(int i = 0; i < exp.size(); i++)
        {
            if(exp[i] != obs[i])
            {
                results += "F";
                passed = false;
                std::cout << "Test FAILED when radius = 2" << std::endl;
                std::cout << "Expected entry " << exp[i].x<<","<< exp[i].z<< ", got " <<obs[i].x<<","<<obs[i].z<< std::endl;
                break;
            }
        }
        if(passed)
        {
            results += ".";
        }
    }

    return results;
}

std::string testGetChunkIDContainingPoint()
{
    std::cout << "\nTesting getChunkIDContainingPoint()" << std::endl;
    std::string results = "";

    std::vector<Point> input {{10, 0, 10}, {500, -20, 500}, {2,7,500}, {500, 0, 2},
                              {20, 0, -758}};
    std::vector<int> exp {0, 0, 0, 0, 14};
    int chunkSize = 512;

    for(int i = 0; i < input.size(); i++)
    {
        int obs = getChunkIDContainingPoint(input[i], chunkSize);
        if(exp[i] != obs)
        {
            results += "F";
            std::cout << "Test FAILED." << std::endl;
            std::cout << "Expected " << exp[i] << ", got  " << obs << std::endl;
        }
    }

    return results;
}

std::string testTrueAngleDifference()
{
    std::cout << "\nTesting trueAngleDifference()" << std::endl;
    std::string results = "";

    std::vector<std::string> descriptions;
    std::vector<double> angle1s;
    std::vector<double> angle2s;
    std::vector<double> exp;
    double tolerance = 0.01;
    double obs;

    descriptions.emplace_back("Q1 - Q1");
    angle1s.push_back(PI/4);
    angle2s.push_back(PI/4);
    exp.push_back(0.0);
    descriptions.emplace_back("Q2 - Q1");
    angle1s.push_back(PI/4);
    angle2s.push_back(3*PI/4);
    exp.push_back(PI/2);
    descriptions.emplace_back("Q1 - Q2");
    angle1s.push_back(3*PI/4);
    angle2s.push_back(PI/4);
    exp.push_back(PI/2);
    descriptions.emplace_back("Q3 - Q1");
    angle1s.push_back(PI/4);
    angle2s.push_back(5*PI/4);
    exp.push_back(PI);
    descriptions.emplace_back("Q1 - Q3");
    angle1s.push_back(5*PI/4);
    angle2s.push_back(PI/4);
    exp.push_back(PI);
    descriptions.emplace_back("Q4 - Q1");
    angle1s.push_back(PI/4);
    angle2s.push_back(7*PI/4);
    exp.push_back(PI/2);
    descriptions.emplace_back("Q1 - Q4");
    angle1s.push_back(7*PI/4);
    angle2s.push_back(PI/4);
    exp.push_back(PI/2);

    for(int i = 0; i < descriptions.size(); i++)
    {
        obs = trueAngleDifference(angle1s[i], angle2s[i]);
        if(std::abs(exp[i] - obs) > tolerance)
        {
            results += "F";
            std::cout << "Test FAILED for " + descriptions[i] << std::endl;
            std::cout << "Expected " << exp[i] << ", got  " << obs << std::endl;
        }
        else
        {
            results += ".";
        }
    }
    return results;
}

std::string testIsInFieldOfView()
{
    std::cout << "\nTesting isInFieldOfView()" << std::endl;
    std::string results = "";

    Point location = {0, 10, 0};
    Point target;
    double xzAngle, yAngle, fov;

    // In field of view
    target = {0, 10, -10};
    xzAngle = 3*PI/2;
    yAngle = 0;
    fov = PI/4;
    if(!isInFieldOfView(target, location, xzAngle, yAngle, fov))
    {
        results += "F";
        std::cout << "Test FAILED for in field of view" << std::endl;
    }
    else
    {
        results += ".";
    }

    // Wrong on the xz plane
    target = {10, 10, 0};
    xzAngle = 3*PI/2;
    yAngle = 0;
    fov = PI/4;
    if(isInFieldOfView(target, location, xzAngle, yAngle, fov))
    {
        results += "F";
        std::cout << "Test FAILED for wrong on xz plane" << std::endl;
    }
    else
    {
        results += ".";
    }

    // Wrong in the y axis
    target = {0, 100, -10};
    xzAngle = 3*PI/2;
    yAngle = 0;
    fov = PI/4;
    if(isInFieldOfView(target, location, xzAngle, yAngle, fov))
    {
        results += "F";
        std::cout << "Test FAILED for wrong in the y axis" << std::endl;
    }
    else
    {
        results += ".";
    }

    // On ground
    target = {0, 0, -50};
    xzAngle = 3*PI/2;
    yAngle = 0;
    fov = PI/6;
    if(!isInFieldOfView(target, location, xzAngle, yAngle, fov))
    {
        results += "F";
        std::cout << "Test FAILED for on ground" << std::endl;
    }
    else
    {
        results += ".";
    }

    // Far away on ground
    target = {0, 0, -1024};
    xzAngle = 3*PI/2;
    yAngle = 0;
    fov = PI/6;
    if(!isInFieldOfView(target, location, xzAngle, yAngle, fov))
    {
        results += "F";
        std::cout << "Test FAILED for far away on ground" << std::endl;
    }
    else
    {
        results += ".";
    }

    // 360 degree view
    target = {1024, 0, 4096};
    xzAngle = 3*PI/2;
    yAngle = 0;
    fov = 2*PI;
    if(!isInFieldOfView(target, location, xzAngle, yAngle, fov))
    {
        results += "F";
        std::cout << "Test FAILED for 360 degree view" << std::endl;
    }
    else
    {
        results += ".";
    }

    return results;
}

std::string testCorrectAlignedRectangularCrossSection()
{
    std::cout << "\nTesting correctAlignedRectangularCrossSection()" << std::endl;
    std::string results = "";

    const double TOLERANCE = 0.01;
    Point c;
    double xw, zw;
    int buffer;

    std::vector<std::string> cases;
    std::vector<Point> inputs;
    std::vector<std::experimental::optional<Point>> exp;
    std::vector<std::experimental::optional<Point>> obs;

    // Fixed parameters
    c = {0, 0, 0};
    xw = 10;
    zw = 20;
    buffer = 2;

    // When the Point does not need to be corrected
    cases.push_back("Way too far left");
    inputs.push_back({-30, 0, 0});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("On the left buffer");
    inputs.push_back({-7, 0, 0});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("Way too far right");
    inputs.push_back({30, 0, 0});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("On the right buffer");
    inputs.push_back({7, 0, 0});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("Way too far up");
    inputs.push_back({0, 0, -30});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("On the top buffer");
    inputs.push_back({0, 0, -12});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("Way too far down");
    inputs.push_back({0, 0, 30});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("On the bottom buffer");
    inputs.push_back({0, 0, 12});
    exp.push_back(std::experimental::nullopt);

    // When the Point does need to be corrected
    cases.push_back("Inside zone 1");
    inputs.push_back({0, 0, -2});
    exp.push_back(std::experimental::optional<Point>({0, 0, -12}));
    cases.push_back("Inside zone 2");
    inputs.push_back({2, 0, 0});
    exp.push_back(std::experimental::optional<Point>({7, 0, 0}));
    cases.push_back("Inside zone 3");
    inputs.push_back({0, 0, 2});
    exp.push_back(std::experimental::optional<Point>({0, 0, 12}));
    cases.push_back("Inside zone 4");
    inputs.push_back({-2, 0, 0});
    exp.push_back(std::experimental::optional<Point>({-7, 0, 0}));

    // Diagonal points outside
    cases.push_back("Point slightly N of NW and outside");
    inputs.push_back({-7, 0, -13});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("Point slightly W of NW and outside");
    inputs.push_back({-8, 0, -12});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("Point slightly N of NE and outside");
    inputs.push_back({7, 0, -13});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("Point slightly E of NE and outside");
    inputs.push_back({8, 0, -12});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("Point slightly S of SE and outside");
    inputs.push_back({7, 0, 13});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("Point slightly E of SE and outside");
    inputs.push_back({8, 0, 12});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("Point slightly S of SW and outside");
    inputs.push_back({-7, 0, 13});
    exp.push_back(std::experimental::nullopt);
    cases.push_back("Point slightly W of SW and outside");
    inputs.push_back({-8, 0, 12});
    exp.push_back(std::experimental::nullopt);

    // Diagonal points inside
    cases.push_back(" Point slightly N of NW and inside buffer");
    inputs.push_back({-5.2, 0, -10.5});
    exp.push_back(std::experimental::optional<Point>({-5.2, 0, -12}));

    for(int i = 0; i < cases.size(); i++)
    {
        std::experimental::optional<Point> obs = correctAlignedRectangularCrossSection(inputs[i], buffer, c, xw, zw);
        if(exp[i])
        {
            if(!obs || distance2d(*exp[i], *obs) > TOLERANCE)
            {
                std::cout << "Test FAILED for " + cases[i] << std::endl;
                results += "F";
            }
            else
            {
                results += ".";
            }
        }
        else
        {
            if(obs)
            {
                std::cout << "Test FAILED for " + cases[i] << std::endl;
                results += "F";
            }
            else
            {
                results += ".";
            }
        }
    }
    return results;
}

std::string testCorrectRectangularCrossSection()
{
    std::cout << "\nTesting correctRectangularCrossSection()" << std::endl;
    std::string results = "";

    const double TOLERANCE = 0.01;
    Point c;
    double xw, zw;
    int buffer;

    std::vector<std::string> cases;
    std::vector<Point> points;
    std::vector<double> angles;
    std::vector<std::experimental::optional<Point>> exp;
    std::vector<std::experimental::optional<Point>> obs;

    // Fixed parameters
    c = {0, 0, 0};
    xw = 10;
    zw = 20;
    buffer = 2;

    cases.push_back("Would have been in, but out due to 45 deg angle");
    angles.push_back(PI/4);
    points.push_back({6, 0, 11});
    exp.push_back(std::experimental::nullopt);

    cases.push_back("Would have been out, but in due to 45 deg angle");
    angles.push_back(PI/4);
    points.push_back({11.313708498984761, 0, -2.8284271247461903});
    exp.push_back(std::experimental::optional<Point>({12.020815280171309, 0, -2.121320343559643}));

    for(int i = 0; i < cases.size(); i++)
    {
        std::experimental::optional<Point> obs = correctRectangularCrossSection(points[i], buffer, c, xw, zw, angles[i]);
        if(exp[i])
        {
            if(!obs || distance2d(*exp[i], *obs) > TOLERANCE)
            {
                std::cout << "Test FAILED for " + cases[i] << std::endl;
                results += "F";
            }
            else
            {
                results += ".";
            }
        }
        else
        {
            if(obs)
            {
                std::cout << "Test FAILED for " + cases[i] << std::endl;
                results += "F";
            }
            else
            {
                results += ".";
            }
        }
    }
    return results;
}
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
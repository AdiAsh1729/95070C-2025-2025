#pragma once

#include <iostream>
#include <vector>

struct Point {
    double xCoordinate;
    double yCoordinate;
};

class Path {
    private:
        std::vector<Point> pathWaypoints;
        double stepAmount;

    public:
        Path(std::vector<Point> pathWaypoints, double stepAmount);

        struct Derivative {
            double xDerivative;
            double yDerivative;
        };

        Derivative getTangent(Point previousPoint, Point nextPoint);
        Point getCubicHermiteSpline(Point initialPoint, Point endPoint, Derivative initialDerivative, Derivative endDerivative, double stepAmount);
        std::vector<Point> generatedPath();
};
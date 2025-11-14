#pragma once

#include <iostream>
#include <vector>

class Path {
    public:
        struct Point {
            double xCoordinate;
            double yCoordinate;
        };

        struct Derivative {
            double xDerivative;
            double yDerivative;
        };

    private:
        std::vector<Point> pathWaypoints;
        double stepAmount;

    public:
        Path(std::vector<Point> pathWaypoints, double stepAmount);

        Derivative getTangent(Point previousPoint, Point nextPoint);
        Point getCubicHermiteSpline(Point initialPoint, Point endPoint, Derivative initialDerivative, Derivative endDerivative, double stepAmount);
        std::vector<Point> generatedPath();
};
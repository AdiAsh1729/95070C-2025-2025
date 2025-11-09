#include "odometry.h"

Odometry::Odometry(double horizontalToCenterDistance, double verticalToCenterDistance):
    horizontalToCenterDistance(horizontalToCenterDistance),
    verticalToCenterDistance(verticalToCenterDistance)
{};

void Odometry::setPosition(double xCoordinate, double yCoordinate, double globalOrientation) {
    this->previousGlobalHorizontal = 0;
    this->previousGlobalVertical = 0;
    this->previousGlobalOrientation = degreesToRadians(globalOrientation);
    this->xCoordinate = xCoordinate;
    this->yCoordinate = yCoordinate;
    this->globalOrientation = globalOrientation;
}
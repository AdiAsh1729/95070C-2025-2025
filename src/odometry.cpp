#include "odometry.h"

Odometry::Odometry(double verticalToCenterDistance):
    verticalToCenterDistance(verticalToCenterDistance)
{};


Odometry::Odometry(double horizontalToCenterDistance, double verticalToCenterDistance):
    horizontalToCenterDistance(horizontalToCenterDistance),
    verticalToCenterDistance(verticalToCenterDistance)
{};

Odometry::setPosition(double xCoordinate, double yCoordinate, double globalOrientation) {
    this->previousHorizontalPosition = 0;
    this->previousVerticalPosition = 0;
    this->previousGlobalOrientation = degreesToRadians(globalOrientation);
    this->xCoordinate = xCoordinate;
    this->yCoordinate = yCoordinate;
    this->globalOrientation = globalOrientation;
}

Odometry::updatePosition(double horizontalTrackerPosition, double verticalTrackerPosition, double globalOrientation) {
    double horizontalDelta = horizontalTrackerPosition - this->previousHorizontalPosition;
    double verticalDelta = verticalTrackerPosition - this->previousVerticalPosition;
    this->globalOrientation = globalOrientation;
    double orientationDelta = this->globalOrientation - this->previousGlobalOrientation;
    double localHorizontalDelta = 2 * sin(orientationDelta/2) * (horizontalDelta/orientationDelta + this->horizontalToCenterDistance);
    double localVerticalDelta = 2 * sin(orientationDelta/2) * (verticalDelta/orientationDelta + this->horizontalToCenterDistance);
}
#pragma once

#include "util.h"

class Odometry {
    private:
        double horizontalWheelDiameter;
        double verticalWheelDiameter;
        double horizontalToCenterDistance;
        double verticalToCenterDistance;
        double previousGlobalHorizontal;
        double previousGlobalVertical;
        double previousGlobalOrientation;

    public:
        Odometry(double horizontalToCenterDistance, double verticalToCenterDistance);

        double xCoordinate;
        double yCoordinate;
        double globalOrientation;

        void setPosition(double xCoordinate, double yCoordinate, double globalOrientation);

        void updatePosition(double horizontalTrackerPosition, double verticalTrackerPosition, double globalOrientation);
}
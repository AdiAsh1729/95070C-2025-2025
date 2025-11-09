#pragma once

#include "util.h"

class Odometry {
    private:
        double horizontalWheelDiameter; //diameter of back wheel
        double verticalWheelDiameter; //diameter of 
        double horizontalToCenterDistance;
        double verticalToCenterDistance;
        double previousGlobalHorizontal;
        double previousGlobalVertical;
        double previousGlobalOrientation;

    public:
        Odometry(double verticalToCenterDistance);
        Odometry(double horizontalToCenterDistance, double verticalToCenterDistance);

        double xCoordinate;
        double yCoordinate;
        double globalOrientation;

        void setPosition(double xCoordinate, double yCoordinate, double globalOrientation);

        void updatePosition(double verticalTrackerPosition, double globalOrientation);
        void updatePosition(double horizontalTrackerPosition, double verticalTrackerPosition, double globalOrientation);
}
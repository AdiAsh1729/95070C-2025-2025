#include "util.h"

double getSign(double input) {
    return (input > 0) - (input < 0);
}

double getTurnError(double heading, double targetHeading) {
    if(std::max(heading, targetHeading) - std::min(heading, targetHeading) <= 180) {
        return targetHeading - heading;
    }

    else {
        if(heading > targetHeading) {
            return targetHeading - heading + 360;
        }

        else {
            return targetHeading - heading - 360;
        }
    }
}

double degreesToRadians(double degrees) {
    return degrees * M_PI / 180;
}

double radiansToDegrees(double radians) {
    return radians * 180 / M_PI;
}
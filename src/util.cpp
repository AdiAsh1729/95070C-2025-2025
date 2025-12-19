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

double clamp(double input, double minimumValue, double maximumValue) {
    // Handle case where min > max (e.g., when dealing with negative values)
    double actualMin = std::min(minimumValue, maximumValue);
    double actualMax = std::max(minimumValue, maximumValue);

    if(input < actualMin) {
        return actualMin;
    }

    else if(input > actualMax) {
        return actualMax;
    }

    else {
        return input;
    }
}

double degreesToRadians(double degrees) {
    return degrees * M_PI / 180;
}

double radiansToDegrees(double radians) {
    return radians * 180 / M_PI;
}

double getGreaterArcDistance(double headingDelta, double radius, double distanceToSideOfDrivetrain) {
    // Arc length = angle (in radians) * radius
    return degreesToRadians(std::abs(headingDelta)) * (radius + distanceToSideOfDrivetrain);
}

double getLesserArcDistance(double headingDelta, double radius, double distanceToSideOfDrivetrain) {
    // Arc length = angle (in radians) * radius
    return degreesToRadians(std::abs(headingDelta)) * (radius - distanceToSideOfDrivetrain);
}
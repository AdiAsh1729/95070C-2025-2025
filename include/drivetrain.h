#pragma once

#include "vex.h"
#include "odometry.h"
#include "PID.h"
#include "util.h"
#include <iostream>
using namespace vex;

enum OdometryType {
    ZeroTrackerOdometry,
    OneTrackerOdometry,
    TwoTrackerOdometry
};

class Drivetrain {
    private:
        brain& Brain;
        motor_group& LeftDrive;
        motor_group& RightDrive;
        rotation& HorizontalTracker;
        rotation& VerticalTracker;
        inertial& Inertial;

        double gearRatio;
        double wheelDiameter;
        double distanceToSideOfDrivetrain;
        double horizontalWheelDiameter;
        double verticalWheelDiameter;
        double horizontalToCenterDistance;
        double verticalToCenterDistance;

        OdometryType odometryType;

        static int trackPosition();
        task positionTrackingTask;

    public:
        Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, inertial& Inertial, double gearRatio, double wheelDiameter, double distanceToSideOfDrivetrain);
        Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, rotation& HorizontalTracker, inertial& Inertial, double gearRatio,  double wheelDiameter, double distanceToSideOfDrivetrain, double horizontalWheelDiameter, double horizontalToCenterDistance);
        Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, rotation& HorizontalTracker, rotation& VerticalTracker, inertial& Inertial, double gearRatio,  double wheelDiameter, double distanceToSideOfDrivetrain, double horizontalWheelDiameter, double verticalWheelDiameter, double horizontalToCenterDistance, double verticalToCenterDistance);

        Odometry odometry;

        void resetHorizontalTrackerPosition();
        void resetVerticalTrackerPosition();
        double getHorizontalTrackerPositionInches();
        double getVerticalTrackerPositionInches();

        void setCoordinates(double initialXCoordinate, double initialYCoordinate, double initialGlobalOrientation);

        typedef struct outputConstants {
            double kp;
            double ki;
            double kd;
        };

        outputConstants driveDistanceConstants;
        outputConstants driveDistanceSlowConstants;
        outputConstants turnToHeadingConstants;
        outputConstants arcConstants;

        void driveDistance(double targetDistance);
        void driveDistance(double targetDistance, double minimumSpeed);

        void driveDistanceSlow(double targetDistance);
        void driveDistanceSlow(double targetDistance, double minimumSpeed);

        void turnToHeading(double targetHeading);

        void arcToHeading(double targetHeading, double radius, double minimumSpeed);

        void oscillate(int numberOfOscillations, double speedOfOscillation, double timeOfOscillation);
};

extern Drivetrain chassis;
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
        double horizontalWheelDiameter;
        double verticalWheelDiameter;
        double horizontalToCenterDistance;
        double verticalToCenterDistance;

        OdometryType odometryType;

        static int trackPosition();
        task positionTrackingTask;

    public:
        Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, inertial& Inertial, double gearRatio, double wheelDiameter);
        Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, rotation& HorizontalTracker, inertial& Inertial, double gearRatio,  double wheelDiameter, double horizontalWheelDiameter, double horizontalToCenterDistance);
        Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, rotation& HorizontalTracker, rotation& VerticalTracker, inertial& Inertial, double gearRatio,  double wheelDiameter, double horizontalWheelDiameter, double verticalWheelDiameter, double horizontalToCenterDistance, double verticalToCenterDistance);

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

        outputConstants driveDistanceLeftConstants;
        outputConstants driveDistanceRightConstants;

        outputConstants driveDistanceSlowLeftConstants;
        outputConstants driveDistanceSlowRightConstants;

        outputConstants turnToHeadingConstants;

        void driveDistance(double targetDistance);
        void driveDistanceSlow(double targetDistance);
        void turnToHeading(double targetHeading);
        void driveToPoint(double targetX, double targetY);
};

extern Drivetrain chassis;
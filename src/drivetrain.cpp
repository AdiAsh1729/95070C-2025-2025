#include "drivetrain.h"

static rotation DummyRotation = rotation(PORT6);

Drivetrain::Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, inertial& Inertial, double gearRatio, double wheelDiameter, double distanceToSideOfDrivetrain):
    Brain(Brain),
    LeftDrive(LeftDrive),
    RightDrive(RightDrive),
    HorizontalTracker(DummyRotation), //unused member
    VerticalTracker(DummyRotation), //unused member
    Inertial(Inertial),
    gearRatio(gearRatio),
    wheelDiameter(wheelDiameter),
    distanceToSideOfDrivetrain(distanceToSideOfDrivetrain),
    odometryType(ZeroTrackerOdometry),
    odometry(0, 0)
{};

Drivetrain::Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, rotation& HorizontalTracker, inertial& Inertial, double gearRatio,  double wheelDiameter, double distanceToSideOfDrivetrain, double horizontalWheelDiameter, double horizontalToCenterDistance):
    Brain(Brain),
    LeftDrive(LeftDrive),
    RightDrive(RightDrive),
    HorizontalTracker(HorizontalTracker),
    VerticalTracker(DummyRotation), //unused member
    Inertial(Inertial),
    gearRatio(gearRatio),
    wheelDiameter(wheelDiameter),
    distanceToSideOfDrivetrain(distanceToSideOfDrivetrain),
    horizontalWheelDiameter(horizontalWheelDiameter),
    horizontalToCenterDistance(horizontalToCenterDistance),
    odometryType(OneTrackerOdometry),
    odometry(horizontalToCenterDistance, 0)
{};

Drivetrain::Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, rotation& HorizontalTracker, rotation& VerticalTracker, inertial& Inertial, double gearRatio,  double wheelDiameter, double distanceToSideOfDrivetrain, double horizontalWheelDiameter, double verticalWheelDiameter, double horizontalToCenterDistance, double verticalToCenterDistance):
    Brain(Brain),
    LeftDrive(LeftDrive),
    RightDrive(RightDrive),
    HorizontalTracker(HorizontalTracker),
    VerticalTracker(VerticalTracker),
    Inertial(Inertial),
    gearRatio(gearRatio),
    wheelDiameter(wheelDiameter),
    distanceToSideOfDrivetrain(distanceToSideOfDrivetrain),
    horizontalWheelDiameter(horizontalWheelDiameter),
    verticalWheelDiameter(verticalWheelDiameter),
    horizontalToCenterDistance(horizontalToCenterDistance),
    verticalToCenterDistance(verticalToCenterDistance),
    odometryType(TwoTrackerOdometry),
    odometry(horizontalToCenterDistance, verticalToCenterDistance)
{};

void Drivetrain::resetHorizontalTrackerPosition() {
    if (this->odometryType == OneTrackerOdometry || this->odometryType == TwoTrackerOdometry) {
        HorizontalTracker.resetPosition();
    }
}

void Drivetrain::resetVerticalTrackerPosition() {
    if (this->odometryType == ZeroTrackerOdometry || this->odometryType == OneTrackerOdometry) {
        LeftDrive.resetPosition();
        RightDrive.resetPosition();
    }

    else if (odometryType == TwoTrackerOdometry) {
        VerticalTracker.resetPosition();
    }
}

double Drivetrain::getHorizontalTrackerPositionInches() {
    if(this->odometryType == OneTrackerOdometry || this->odometryType == TwoTrackerOdometry) {
        return HorizontalTracker.position(turns) * M_PI * this->horizontalWheelDiameter;
    }

    else {
        return 0;
    }
}

double Drivetrain::getVerticalTrackerPositionInches() {
    if(this->odometryType == ZeroTrackerOdometry || this->odometryType == OneTrackerOdometry) {
        return (LeftDrive.position(turns) + RightDrive.position(turns))/2 * M_PI * this->wheelDiameter * this->gearRatio;
    }

    else if(this->odometryType == TwoTrackerOdometry) {
        return VerticalTracker.position(turns) * M_PI * this->verticalWheelDiameter;
    }

    else {
        return 0;
    }
}

void Drivetrain::setCoordinates(double initialXCoordinate, double initialYCoordinate, double initialGlobalOrientation) {
    resetHorizontalTrackerPosition();
    resetVerticalTrackerPosition();
    Inertial.setHeading(initialGlobalOrientation, deg);
    odometry.setPosition(initialXCoordinate, initialYCoordinate, initialGlobalOrientation);

    positionTrackingTask = task(trackPosition);
}

int Drivetrain::trackPosition() {
    while(true) {
        chassis.odometry.updatePosition(chassis.getHorizontalTrackerPositionInches(), chassis.getVerticalTrackerPositionInches(), chassis.Inertial.heading(degrees));

        wait(5, msec);
    }

    return 0;
}

//drive a straight line distance
void Drivetrain::driveDistance(double targetDistance) {
    timer DrivePIDTimer;
    DrivePIDTimer.clear();

    PID drivePID(targetDistance, targetDistance, driveDistanceConstants.kp, driveDistanceConstants.ki, driveDistanceConstants.kd, 10, 0, 0, targetDistance, 0.5, 0, 0, targetDistance * 50);

    LeftDrive.resetPosition();
    RightDrive.resetPosition();

    do {
        drivePID.error = drivePID.startError - (LeftDrive.position(turns) + RightDrive.position(turns))/2 * (this->wheelDiameter) * M_PI * (this->gearRatio);

        drivePID.motorOutput = drivePID.output();
        
        if((LeftDrive.velocity(pct) == 0 && RightDrive.velocity(pct) != 0) || (LeftDrive.velocity(pct) != 0 && RightDrive.velocity(pct) == 0)) {
            drivePID.motorOutput = 0;
        }

        LeftDrive.spin(forward, drivePID.motorOutput, pct);
        RightDrive.spin(forward, drivePID.motorOutput, pct);

        std::cout << LeftDrive.position(turns) * (this->wheelDiameter) * M_PI * (this->gearRatio) << ", " << RightDrive.position(turns) * (this->wheelDiameter) * M_PI * (this->gearRatio) << ", " << Inertial.heading() << std::endl;

        drivePID.timeSpent += 20;
        wait(20, msec);
    } while(!drivePID.settled());
    
    std::cout << "DrivePID is done!" << std::endl;
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
};

//drive a straight line distance + motion chaining
void Drivetrain::driveDistance(double targetDistance, double minimumSpeed) {
    PID drivePID(targetDistance, targetDistance, driveDistanceConstants.kp, driveDistanceConstants.ki, driveDistanceConstants.kd, 10, 0, 0, targetDistance, 0.5, 0, 1.5, 0);

    LeftDrive.resetPosition();
    RightDrive.resetPosition();

    do {
        drivePID.error = drivePID.startError - (LeftDrive.position(turns) + RightDrive.position(turns))/2 * (this->wheelDiameter) * M_PI * (this->gearRatio);

        drivePID.motorOutput = clamp(drivePID.output(), getSign(drivePID.startError) * minimumSpeed, getSign(drivePID.startError) * 99.9);

        LeftDrive.spin(forward, drivePID.motorOutput, pct);
        RightDrive.spin(forward, drivePID.motorOutput, pct);

        drivePID.timeSpent += 20;
        wait(20, msec);
    } while(!drivePID.settled());

    std::cout << "DrivePID is done!" << std::endl;
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
};


//drive a straight line distance slowly
void Drivetrain::driveDistanceSlow(double targetDistance) {
    PID drivePID(targetDistance, targetDistance, driveDistanceSlowConstants.kp, driveDistanceSlowConstants.ki, driveDistanceSlowConstants.kd, 10, 0, 0, targetDistance, 1, 0, 1.5, 0);

    LeftDrive.resetPosition();
    RightDrive.resetPosition();

    do {
        drivePID.error = drivePID.startError - (LeftDrive.position(turns) + RightDrive.position(turns))/2 * (this->wheelDiameter) * M_PI * (this->gearRatio);
        
        drivePID.motorOutput = drivePID.output();

        if((LeftDrive.velocity(pct) == 0 && RightDrive.velocity(pct) != 0) || (LeftDrive.velocity(pct) != 0 && RightDrive.velocity(pct) == 0)) {
            drivePID.motorOutput = 0;
        }

        LeftDrive.spin(forward, drivePID.motorOutput, pct);
        RightDrive.spin(forward, drivePID.motorOutput, pct);

        drivePID.timeSpent += 20;
        wait(20, msec);
    } while(!drivePID.settled());

    std::cout << "DriveSlowPID is done!" << std::endl;
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
};

//drive a straight line distance slowly + motion chaining
void Drivetrain::driveDistanceSlow(double targetDistance, double minimumSpeed) {
    PID drivePID(targetDistance, targetDistance, driveDistanceSlowConstants.kp, driveDistanceSlowConstants.ki, driveDistanceSlowConstants.kd, 10, 0, 0, targetDistance, 1, 0, 1.5, 0);

    LeftDrive.resetPosition();
    RightDrive.resetPosition();

    do {
        drivePID.error = drivePID.startError - (LeftDrive.position(turns) + RightDrive.position(turns))/2 * (this->wheelDiameter) * M_PI * (this->gearRatio);
        
        drivePID.motorOutput = clamp(drivePID.output(), getSign(drivePID.startError) * minimumSpeed, getSign(drivePID.startError) * 99.9);

        LeftDrive.spin(forward, drivePID.motorOutput, pct);
        RightDrive.spin(forward, drivePID.motorOutput, pct);

        drivePID.timeSpent += 20;
        wait(20, msec);
    } while(!drivePID.settled());

    std::cout << "DriveSlowPID is done!" << std::endl;
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
};


//turn to a global heading
void Drivetrain::turnToHeading(double targetHeading) {
    PID turnPID(targetHeading, targetHeading, turnToHeadingConstants.kp, turnToHeadingConstants.ki, turnToHeadingConstants.kd, targetHeading/5, 0, 0, targetHeading, 3, 0, 1.5, 0);

    do {
        turnPID.error = getTurnError(Inertial.heading(), targetHeading);

        turnPID.motorOutput = turnPID.output();

        LeftDrive.spin(forward, turnPID.motorOutput, pct);
        RightDrive.spin(reverse, turnPID.motorOutput, pct);

        turnPID.timeSpent += 20;
        wait(20, msec);
    } while(!turnPID.settled());

    std::cout << "TurnPID is done!" << std::endl;
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
};

void Drivetrain::arcToHeading(double targetHeading, double radius, double minimumSpeed) {
    double turnError = getTurnError(Inertial.heading(), targetHeading);
    double leftArcDist, rightArcDist;

    if(turnError > 0) {
        leftArcDist = getGreaterArcDistance(turnError, radius, this->distanceToSideOfDrivetrain);
        rightArcDist = getLesserArcDistance(turnError, radius, this->distanceToSideOfDrivetrain);
    } else {
        leftArcDist = getLesserArcDistance(turnError, radius, this->distanceToSideOfDrivetrain);
        rightArcDist = getGreaterArcDistance(turnError, radius, this->distanceToSideOfDrivetrain);
    }

    PID arcLeftPID(leftArcDist, leftArcDist, arcConstants.kp, arcConstants.ki, arcConstants.kd, leftArcDist/5, 0, 0, leftArcDist, 3, 0, 1.5, 0);
    PID arcRightPID(rightArcDist, rightArcDist, arcConstants.kp, arcConstants.ki, arcConstants.kd, rightArcDist/5, 0, 0, rightArcDist, 3, 0, 1.5, 0);

    do {
        arcLeftPID.error = getTurnError(Inertial.heading(), targetHeading);
        arcRightPID.error = getTurnError(Inertial.heading(), targetHeading);

        arcLeftPID.motorOutput = arcLeftPID.output();
        arcRightPID.motorOutput = arcRightPID.output();

        LeftDrive.spin(forward, arcLeftPID.motorOutput, pct);
        RightDrive.spin(reverse, arcRightPID.motorOutput, pct);

        arcLeftPID.timeSpent += 20;
        arcRightPID.timeSpent += 20;
        wait(20, msec);
    } while(!arcLeftPID.settled() || !arcRightPID.settled());

    std::cout << "ArcPIDs are done!" << std::endl;
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
}

void Drivetrain::oscillate(int numberOfOscillations, double speedOfOscillation, double timeOfOscillation) {
    for(int i = 0; i < numberOfOscillations; i++) {
        LeftDrive.spin(forward, speedOfOscillation, pct);
        RightDrive.spin(forward, speedOfOscillation, pct);
        wait(timeOfOscillation, msec);
        LeftDrive.spin(reverse, speedOfOscillation, pct);
        RightDrive.spin(reverse, speedOfOscillation, pct);
        if(i < numberOfOscillations - 1) {
            wait(timeOfOscillation, msec);
        }
    }
}


#include "drivetrain.h"

static rotation DummyRotation = rotation(PORT6);

Drivetrain::Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, inertial& Inertial, double gearRatio, double wheelDiameter):
    Brain(Brain),
    LeftDrive(LeftDrive),
    RightDrive(RightDrive),
    HorizontalTracker(DummyRotation), //unused member
    VerticalTracker(DummyRotation), //unused member
    Inertial(Inertial),
    gearRatio(gearRatio),
    wheelDiameter(wheelDiameter),
    odometryType(ZeroTrackerOdometry),
    odometry(0, 0)
{};

Drivetrain::Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, rotation& HorizontalTracker, inertial& Inertial, double gearRatio,  double wheelDiameter, double horizontalWheelDiameter, double horizontalToCenterDistance):
    Brain(Brain),
    LeftDrive(LeftDrive),
    RightDrive(RightDrive),
    HorizontalTracker(HorizontalTracker),
    VerticalTracker(DummyRotation), //unused member
    Inertial(Inertial),
    gearRatio(gearRatio),
    wheelDiameter(wheelDiameter),
    horizontalWheelDiameter(horizontalWheelDiameter),
    horizontalToCenterDistance(horizontalToCenterDistance),
    odometryType(OneTrackerOdometry),
    odometry(horizontalToCenterDistance, 0)
{};

Drivetrain::Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, rotation& HorizontalTracker, rotation& VerticalTracker, inertial& Inertial, double gearRatio,  double wheelDiameter, double horizontalWheelDiameter, double verticalWheelDiameter, double horizontalToCenterDistance, double verticalToCenterDistance):
    Brain(Brain),
    LeftDrive(LeftDrive),
    RightDrive(RightDrive),
    HorizontalTracker(HorizontalTracker),
    VerticalTracker(VerticalTracker),
    Inertial(Inertial),
    gearRatio(gearRatio),
    wheelDiameter(wheelDiameter),
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
        return (LeftDrive.position(turns) + RightDrive.position(turns))/2 * M_PI * this->wheelDiameter;
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

void Drivetrain::driveDistance(double targetDistance) { //converting to volts makes it very smooth
    PID drivePID(targetDistance, targetDistance, driveDistanceConstants.kp, driveDistanceConstants.ki, driveDistanceConstants.kd, targetDistance/5, 0, 0, targetDistance, 0.5, 0);

    LeftDrive.resetPosition();
    RightDrive.resetPosition();

    do {
        drivePID.error = drivePID.startError - (LeftDrive.position(turns) + RightDrive.position(turns))/2 * (this->wheelDiameter) * M_PI * (this->gearRatio);

        drivePID.motorOutput = drivePID.output();
        
        LeftDrive.spin(forward, percentToVolts(drivePID.motorOutput), volt);
        RightDrive.spin(forward, percentToVolts(drivePID.motorOutput), volt);

        wait(20, msec);
    } while(!drivePID.settled());
    
    std::cout << "DrivePID is done!" << std::endl;
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
};

void Drivetrain::driveDistancePct(double targetDistance) { //converting to volts makes it very smooth
    PID drivePID(targetDistance, targetDistance, driveDistanceConstants.kp, driveDistanceConstants.ki, driveDistanceConstants.kd, targetDistance/5, 0, 0, targetDistance, 0.5, 0);

    LeftDrive.resetPosition();
    RightDrive.resetPosition();

    do {
        drivePID.error = drivePID.startError - (LeftDrive.position(turns) + RightDrive.position(turns))/2 * (this->wheelDiameter) * M_PI * (this->gearRatio);

        drivePID.motorOutput = drivePID.output();
        
        LeftDrive.spin(forward, drivePID.motorOutput, pct);
        RightDrive.spin(forward, drivePID.motorOutput, pct);

        wait(20, msec);
    } while(!drivePID.settled());
    
    std::cout << "DrivePID is done!" << std::endl;
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
};

void Drivetrain::driveDistanceSlow(double targetDistance) { //converting to volts makes (almost) 2 seperate movements: before and after integral term is applied
    PID drivePID(targetDistance, targetDistance, driveDistanceSlowConstants.kp, driveDistanceSlowConstants.ki, driveDistanceSlowConstants.kd, targetDistance/5, 0, 0, targetDistance, 1, 0);

    LeftDrive.resetPosition();
    RightDrive.resetPosition();

    do {
        drivePID.error = drivePID.startError - (LeftDrive.position(turns) + RightDrive.position(turns))/2 * (this->wheelDiameter) * M_PI * (this->gearRatio);
        
        drivePID.motorOutput = drivePID.output();

        LeftDrive.spin(forward, drivePID.motorOutput, pct);
        RightDrive.spin(forward, drivePID.motorOutput, pct);

        wait(20, msec);
    } while(!drivePID.settled());
    
    std::cout << "DriveSlowPID is done!" << std::endl;
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
};

void Drivetrain::turnToHeading(double targetHeading) { //converting to volts makes a very smooth undershoot (by a lot)
    PID turnPID(targetHeading, targetHeading, turnToHeadingConstants.kp, turnToHeadingConstants.ki, turnToHeadingConstants.kd, targetHeading/5, 0, 0, targetHeading, 3, 0);

    do {
        turnPID.error = getTurnError(Inertial.heading(), targetHeading);

        turnPID.motorOutput = turnPID.output();

        LeftDrive.spin(forward, turnPID.motorOutput, pct);
        RightDrive.spin(reverse, turnPID.motorOutput, pct);

        wait(20, msec);
    } while(!turnPID.settled());


    std::cout << "TurnPID is done!" << std::endl;
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
};

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


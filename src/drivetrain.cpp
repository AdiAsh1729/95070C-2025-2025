#include "drivetrain.h"

static rotation DummyRotation = rotation(PORT6); //port 6 is bad

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
    if (odometryType == OneTrackerOdometry || odometryType == TwoTrackerOdometry) {
        HorizontalTracker.resetPosition();
    }
}

void Drivetrain::resetVerticalTrackerPosition() {
    if (odometryType == ZeroTrackerOdometry || odometryType == OneTrackerOdometry) {
        LeftDrive.resetPosition();
        RightDrive.resetPosition();
    }

    else if (odometryType == TwoTrackerOdometry) {
        VerticalTracker.resetPosition();
    }
}

double Drivetrain::getHorizontalTrackerPositionInches() {
    if(odometryType == OneTrackerOdometry || odometryType == TwoTrackerOdometry) {
        return HorizontalTracker.position(turns) * M_PI * horizontalWheelDiameter;
    }

    else {
        return 0;
    }
}

double Drivetrain::getVerticalTrackerPositionInches() {
    if(odometryType == ZeroTrackerOdometry || odometryType == OneTrackerOdometry) {
        return (LeftDrive.position(turns) + RightDrive.position(turns))/2 * M_PI * horizontalWheelDiameter;
    }

    else if(odometryType == TwoTrackerOdometry) {
        return VerticalTracker.position(turns) * M_PI * verticalWheelDiameter;
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

void Drivetrain::driveDistance(double targetDistance) {
    PID driveLeftPID(targetDistance, targetDistance, driveDistanceLeftConstants.kp, driveDistanceLeftConstants.ki, driveDistanceLeftConstants.kd, targetDistance/5, 0, 0, targetDistance, 0.2, 0, 0);
    PID driveRightPID(targetDistance, targetDistance, driveDistanceRightConstants.kp, driveDistanceRightConstants.ki, driveDistanceRightConstants.kd, targetDistance/5, 0, 0, targetDistance, 0.2, 0, 0);

    LeftDrive.resetPosition();
    RightDrive.resetPosition();

    do {
        driveLeftPID.error = driveLeftPID.startError - LeftDrive.position(turns) * (this->wheelDiameter) * M_PI * (this->gearRatio);
        driveRightPID.error = driveRightPID.startError - RightDrive.position(turns) * (this->wheelDiameter) * M_PI * (this->gearRatio);
        
        LeftDrive.spin(forward, driveLeftPID.output(), pct);
        RightDrive.spin(forward, driveRightPID.output(), pct);

        wait(20, msec);
    } while(!driveLeftPID.settled() || !driveRightPID.settled());
    
    std::cout << "DrivePID is done!" << std::endl;
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
};

void Drivetrain::driveDistanceSlow(double targetDistance) {
    PID driveLeftPID(targetDistance, targetDistance, driveDistanceSlowLeftConstants.kp, driveDistanceSlowLeftConstants.ki, driveDistanceSlowLeftConstants.kd, targetDistance/5, 0, 0, targetDistance, 1, 0, 0);
    PID driveRightPID(targetDistance, targetDistance, driveDistanceSlowRightConstants.kp, driveDistanceSlowRightConstants.ki, driveDistanceSlowRightConstants.kd, targetDistance/5, 0, 0, targetDistance, 1, 0, 0);

    LeftDrive.resetPosition();
    RightDrive.resetPosition();

    do {
        //Brain.Timer.clear();
        driveLeftPID.error = driveLeftPID.startError - LeftDrive.position(turns) * (this->wheelDiameter) * M_PI * (this->gearRatio);
        driveRightPID.error = driveRightPID.startError - RightDrive.position(turns) * (this->wheelDiameter) * M_PI * (this->gearRatio);

        std::cout << driveLeftPID.error << ", " << driveRightPID.error << std::endl;
        
        driveLeftPID.motorOutput = driveLeftPID.output();
        driveRightPID.motorOutput = driveRightPID.output();
        
        LeftDrive.spin(forward, driveLeftPID.motorOutput, pct);
        RightDrive.spin(forward, driveRightPID.motorOutput, pct);

        wait(20, msec);
    } while(!driveLeftPID.settled() || !driveRightPID.settled());
    
    std::cout << "DriveSlowPID is done!" << std::endl;
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
};

void Drivetrain::turnToHeading(double targetHeading) {
    PID turnPID(targetHeading, targetHeading, turnToHeadingConstants.kp, turnToHeadingConstants.ki, turnToHeadingConstants.kd, targetHeading/5, 0, 0, targetHeading, 3, 0, 0);

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

void Drivetrain::driveToPoint(double targetX, double targetY) {
    double xDelta = 0;
    double yDelta = 0;
    double targetDistance = 0;
    double targetHeading = 0;

    do {
        xDelta = targetX - odometry.xCoordinate;
        std::cout << xDelta << std::endl;
        yDelta = targetY - odometry.yCoordinate;
        std::cout << yDelta << std::endl;
        
        targetDistance = sqrt(pow(xDelta, 2) + pow(yDelta, 2));
        std::cout << targetDistance << std::endl;
        targetHeading = radiansToDegrees(atan2(yDelta, xDelta));
        std::cout << targetHeading << std::endl;

        if(getTurnError(Inertial.heading(), targetHeading) > 3) {
            this->turnToHeading(targetHeading);
        }

        else {
            this->driveDistanceSlow(targetDistance);
        }
    } while(std::abs(xDelta) >= 1.5 || std::abs(yDelta) >= 1.5);
};
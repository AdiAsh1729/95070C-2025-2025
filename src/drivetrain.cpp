#include "drivetrain.h"

Drivetrain::Drivetrain(brain& Brain, motor_group& LeftDrive, motor_group& RightDrive, inertial& Inertial, double gearRatio, double wheelDiameter):
    Brain(Brain),
    LeftDrive(LeftDrive),
    RightDrive(RightDrive),
    Inertial(Inertial),
    gearRatio(gearRatio),
    wheelDiameter(wheelDiameter)
{};

void Drivetrain::driveDistance(double targetDistance) {
    PID driveLeftPID(targetDistance, targetDistance, 0, 0.0015, 0.65, targetDistance/5, 0, 0, targetDistance, 0.2, 0);
    PID driveRightPID(targetDistance, targetDistance, 0, 0.0015, 0.65, targetDistance/5, 0, 0, targetDistance, 0.2, 0);
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
    PID driveLeftPID(targetDistance, targetDistance, 0.75, 0, 0.1, targetDistance/5, 0, 0, targetDistance, 0.1, 0);
    PID driveRightPID(targetDistance, targetDistance, 0.75, 0, 0.1, targetDistance/5, 0, 0, targetDistance, 0.1, 0);

    LeftDrive.resetPosition();
    RightDrive.resetPosition();

    do {
        //Brain.Timer.clear();
        driveLeftPID.error = driveLeftPID.startError - LeftDrive.position(turns) * (this->wheelDiameter) * M_PI * (this->gearRatio);
        driveRightPID.error = driveRightPID.startError - RightDrive.position(turns) * (this->wheelDiameter) * M_PI * (this->gearRatio);
        
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
    PID turnPID(targetHeading, targetHeading, 0.2, 0, 0, targetHeading/5, 0, 0, targetHeading, 3, 0);

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

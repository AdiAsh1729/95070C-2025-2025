#include "driver-control.h"

void runIfPressingMotor(motor& Motor, const controller::button& ButtonForward, const controller::button& ButtonReverse, int forwardVelocityPct, int reverseVelocityPct) {
    if(ButtonForward.pressing()) {
        Motor.spin(forward, forwardVelocityPct, pct);
    }

    else if(ButtonReverse.pressing()) {
        Motor.spin(reverse, reverseVelocityPct, pct);
    }

    else {
        Motor.stop();
    }
}

void runIfPressingMotorGroup(motor_group& MotorGroup, const controller::button& ButtonForward, const controller::button& ButtonReverse, int forwardVelocityPct, int reverseVelocityPct) {
    if(ButtonForward.pressing()) {
        MotorGroup.spin(forward, forwardVelocityPct, pct);
    }

    else if(ButtonReverse.pressing()) {
        MotorGroup.spin(reverse, reverseVelocityPct, pct);
    }

    else {
        MotorGroup.stop();
    }
}

void runIfPressedMotor(motor& Motor, const controller::button& ButtonForward, const controller::button& ButtonReverse, const controller::button& ButtonStop, int forwardVelocityPct, int reverseVelocityPct) {
    if(ButtonForward.pressing()) {
        Motor.spin(forward, forwardVelocityPct, pct);
    }

    else if(ButtonReverse.pressing()) {
        Motor.spin(reverse, reverseVelocityPct, pct);
    }

    else if(ButtonStop.pressing()) {
        Motor.stop();
    }
}

void runIfPressedMotorGroup(motor_group& MotorGroup, const controller::button& ButtonForward, const controller::button& ButtonReverse, const controller::button& ButtonStop, int forwardVelocityPct, int reverseVelocityPct) {
    if(ButtonForward.pressing()) {
        MotorGroup.spin(forward, forwardVelocityPct, pct);
    }

    else if(ButtonReverse.pressing()) {
        MotorGroup.spin(reverse, reverseVelocityPct, pct);
    }

    else if(ButtonStop.pressing()) {
        MotorGroup.stop();
    }
}

void runArcadeDrive(motor_group& LeftDrive, motor_group& RightDrive, controller& Controller, const controller::button& SlowButton, double scaleDriveSpeed, double scaleTurnSpeed) {
    static double totalCount = 0;
    static double totalRatio = 0;

    double buttonScaleSpeed = 1;
    if(SlowButton.pressing()) {
        buttonScaleSpeed = 0.1;
    }
    else {
        buttonScaleSpeed = 1;
    }
    double DriveSpeed = (Controller.Axis3.position()) * scaleDriveSpeed * buttonScaleSpeed;
    double TurnSpeed = (Controller.Axis1.position()) * scaleTurnSpeed * buttonScaleSpeed;
    
    LeftDrive.setStopping(coast);
    RightDrive.setStopping(coast);

    LeftDrive.setVelocity((DriveSpeed + TurnSpeed), pct);
    RightDrive.setVelocity((DriveSpeed - TurnSpeed), pct);

<<<<<<< HEAD
    std::cout << DriveSpeed << std::endl;
=======
    if(RightDrive.velocity(pct) > 0) {
        totalCount++;
        totalRatio += LeftDrive.velocity(pct)/RightDrive.velocity(pct);
    }

    std::cout << totalRatio/totalCount/*(LeftDrive.velocity(pct) + RightDrive.velocity(pct))/2*/ << std::endl;
>>>>>>> 2597543d00a13b769a7d9a7e46102094d7318bb8

    LeftDrive.spin(forward);
    RightDrive.spin(forward);
}

void rotationTest(double RPM) {
    LeftDrive.spin(forward, RPM, rpm);
    RightDrive.spin(forward, RPM, rpm);
    wait(80000/RPM, msec);
    LeftDrive.stop(hold);
    RightDrive.stop(hold);
    std::cout << LeftDrive.position(turns) * 3/4 << ", " << RightDrive.position(turns) * 3/4 << std::endl;
}

void rotationTest2(double velocity) {
    LeftDrive.resetPosition();
    RightDrive.resetPosition();
    LeftDrive.spin(forward, velocity, pct);
    RightDrive.spin(forward, velocity, pct);
    wait(40000/(3*velocity), msec);
    LeftDrive.stop(brake);
    RightDrive.stop(brake);
    std::cout << LeftDrive.position(turns) * 3/4 << ", " << RightDrive.position(turns) * 3/4 << std::endl;
}

void descore_middleGoal() {
    DMPressed ++;
    if((DMPressed)%2 == 0) {
        Descore_MiddleGoal.set(true);
    }

    else {
        Descore_MiddleGoal.set(false);
    }
}

void matchload() {
    MatchloadPressed ++;

    if((MatchloadPressed)%2 == 0) {
        Matchloader.set(false);
    }

    else {
        Matchloader.set(true);
    }
}

void doublePark() {
    ParkPressed ++;

    if((ParkPressed)%2 == 0) {
        Park.set(true);
    }

    else {
        Park.set(false);
    }
}

void moveIntake() {
    switch(CurrentDriver) {
        case Daniel:
            runIfPressedMotor(Intake1, Controller.ButtonR2, Controller.ButtonR1, Controller.ButtonB, 99, 50);
            //runIfPressedMotor(Intake2, Controller.ButtonY, Controller.ButtonR2, Controller.ButtonB, 25);
            runIfPressedMotorGroup(Intake, Controller.ButtonL2, Controller.ButtonUp, Controller.ButtonB, 99, 50);
            break;

        case Thomas:
            runIfPressedMotor(Intake1, Controller.ButtonR1, Controller.ButtonR2, Controller.ButtonB, 99, 99);
            runIfPressedMotorGroup(Intake, Controller.ButtonL1, Controller.ButtonL2, Controller.ButtonB, 99, 99);
            break;

        case Nikhil:
            runIfPressedMotor(Intake1, Controller.ButtonR1, Controller.ButtonR2, Controller.ButtonB, 99, 99);
            runIfPressedMotorGroup(Intake, Controller.ButtonL1, Controller.ButtonL2, Controller.ButtonB, 99, 99);
            break;

        case Shaurya:
            runIfPressedMotor(Intake1, Controller.ButtonR1, Controller.ButtonR2, Controller.ButtonB, 99, 99);
            runIfPressedMotorGroup(Intake, Controller.ButtonL1, Controller.ButtonL2, Controller.ButtonB, 99, 99);
            break;

        case Noob:
            runIfPressedMotor(Intake1, Controller.ButtonR2, Controller.ButtonR1, Controller.ButtonB, 99, 99);
            runIfPressedMotorGroup(Intake, Controller.ButtonL2, Controller.ButtonUp, Controller.ButtonB, 99, 99);
            break;
    }
}

void moveDrivetrain() {
    switch(CurrentDriver) {
        case Daniel:
            runArcadeDrive(LeftDrive, RightDrive, Controller, Controller.ButtonL1, 0.95, 0.90);
            break;

        case Thomas:
            runArcadeDrive(LeftDrive, RightDrive, Controller, Controller.ButtonUp, -0.40, 0.30);
            break;

        case Nikhil:
            runArcadeDrive(LeftDrive, RightDrive, Controller, Controller.ButtonUp, 0.70, 0.30);
            break;

        case Shaurya:
            runArcadeDrive(LeftDrive, RightDrive, Controller, Controller.ButtonUp, 0.45, 0.4367911);
            break;

        case Noob:
            runArcadeDrive(LeftDrive, RightDrive, Controller, Controller.ButtonUp, 0.10, 0.10);
            break;
    }
}
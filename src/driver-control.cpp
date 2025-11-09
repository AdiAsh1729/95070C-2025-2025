#include "driver-control.h"

void runIfPressingMotor(motor& Motor, const controller::button& ButtonForward, const controller::button& ButtonReverse, int velocityPct) {
    if(ButtonForward.pressing()) {
        Motor.spin(forward, velocityPct, pct);
    }

    else if(ButtonReverse.pressing()) {
        Motor.spin(reverse, velocityPct, pct);
    }

    else {
        Motor.stop();
    }
}

void runIfPressingMotorGroup(motor_group& MotorGroup, const controller::button& ButtonForward, const controller::button& ButtonReverse, int velocityPct) {
    if(ButtonForward.pressing()) {
        MotorGroup.spin(forward, velocityPct, pct);
    }

    else if(ButtonReverse.pressing()) {
        MotorGroup.spin(reverse, velocityPct, pct);
    }

    else {
        MotorGroup.stop();
    }
}

void runIfPressedMotor(motor& Motor, const controller::button& ButtonForward, const controller::button& ButtonReverse, const controller::button& ButtonStop, int velocityPct) {
    if(ButtonForward.pressing()) {
        Motor.spin(forward, velocityPct, pct);
    }

    else if(ButtonReverse.pressing()) {
        Motor.spin(reverse, velocityPct, pct);
    }

    else if(ButtonStop.pressing()) {
        Motor.stop();
    }
}

void runIfPressedMotorGroup(motor_group& MotorGroup, const controller::button& ButtonForward, const controller::button& ButtonReverse, const controller::button& ButtonStop, int velocityPct) {
    if(ButtonForward.pressing()) {
        MotorGroup.spin(forward, velocityPct, pct);
    }

    else if(ButtonReverse.pressing()) {
        MotorGroup.spin(reverse, velocityPct, pct);
    }

    else if(ButtonStop.pressing()) {
        MotorGroup.stop();
    }
}

void runArcadeDrive(motor_group& LeftDrive, motor_group& RightDrive, controller& Controller, const controller::button& SlowButton, double scaleDriveSpeed, double scaleTurnSpeed) {
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

    LeftDrive.setVelocity((DriveSpeed - TurnSpeed), pct);
    RightDrive.setVelocity((DriveSpeed + TurnSpeed), pct);

    LeftDrive.spin(forward);
    RightDrive.spin(forward);
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
            runIfPressedMotor(Intake1, Controller.ButtonR2, Controller.ButtonR1, Controller.ButtonB, 99);
            runIfPressedMotorGroup(Intake, Controller.ButtonL2, Controller.ButtonUp, Controller.ButtonB, 99);
            break;

        case Thomas:
            runIfPressedMotor(Intake1, Controller.ButtonR1, Controller.ButtonR2, Controller.ButtonB, 99);
            runIfPressedMotorGroup(Intake, Controller.ButtonL1, Controller.ButtonL2, Controller.ButtonB, 99);
            break;

        case Nikhil:
            runIfPressedMotor(Intake1, Controller.ButtonR1, Controller.ButtonR2, Controller.ButtonB, 99);
            runIfPressedMotorGroup(Intake, Controller.ButtonL1, Controller.ButtonL2, Controller.ButtonB, 99);
            break;

        case Shaurya:
            runIfPressedMotor(Intake1, Controller.ButtonR1, Controller.ButtonR2, Controller.ButtonB, 99);
            runIfPressedMotorGroup(Intake, Controller.ButtonL1, Controller.ButtonL2, Controller.ButtonB, 99);
            break;

        case Noob:
            runIfPressedMotor(Intake1, Controller.ButtonR2, Controller.ButtonR1, Controller.ButtonB, 99);
            runIfPressedMotorGroup(Intake, Controller.ButtonL2, Controller.ButtonUp, Controller.ButtonB, 99);
            break;
    }
}

void moveDrivetrain() {
    switch(CurrentDriver) {
        case Daniel:
            runArcadeDrive(LeftDrive, RightDrive, Controller, Controller.ButtonL1, 0.99, 0.95);
            break;

        case Thomas:
            runArcadeDrive(LeftDrive, RightDrive, Controller, Controller.ButtonUp, 0.38, 0.30);
            break;

        case Nikhil:
            runArcadeDrive(LeftDrive, RightDrive, Controller, Controller.ButtonUp, 0.4567911, 0.4367911);
            break;

        case Shaurya:
            runArcadeDrive(LeftDrive, RightDrive, Controller, Controller.ButtonUp, 0.45, 0.4367911);
            break;

        case Noob:
            runArcadeDrive(LeftDrive, RightDrive, Controller, Controller.ButtonUp, 0.10, 0.10);
            break;
    }
}
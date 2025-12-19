#include "vex.h"
#include "autons.h"
#include "auton-selector.h"
#include "driver-control.h"
#include "pressed.h"
#include <iostream>

competition Competition;

Drivetrain chassis(Brain, LeftDrive, RightDrive, Inertial, 0.75, 3.25, 100); //100 is a dummy value representing the distance to side of drivetrain

void preAuton(void) {
    vexcodeInit();
    // Calibrate Inertial Sensors
    Inertial.calibrate();
    wait(3, sec);
    Inertial.resetHeading();
    displayAuton();
    //Select Auton
    while(true) {
        if(pressed(Controller.ButtonRight, Right)) {
            changeAutonRight();
        }
        if(pressed(Controller.ButtonLeft, Left)) {
            changeAutonLeft();
        }
        if(pressed(Controller.ButtonA, A)) {
            ifAutonButtonPressed();
        }
        if(AutonButtonPressed) {
            resetPressed();
            Controller.rumble("-");
            RunningAuton = false;
            break;
        }
        wait(20, msec);
    }

    wait(1, sec);
    
    //Checks if running DriverSkills(if) or Auton(else)
    if(CurrentAuton == Null) {
        displayDriver();
        //Select Driver
        while(true) {
            if(pressed(Controller.ButtonRight, Right)) {
                changeDriverRight();
            }
            if(pressed(Controller.ButtonLeft, Left)) {
                changeDriverLeft();
            }
            if(pressed(Controller.ButtonA, A)) {
                ifDriverButtonPressed();
            }
            if(DriverButtonPressed) {
                resetPressed();
                Controller.rumble("-");
                RunningPreAuton = false;
                return;
            }
            wait(20, msec);
        }
    }

    else {
        RunningPreAuton = false;
        wait(20, msec);
        return;
    }
}

void autonomous() {
    timer autonTimer;
    autonTimer.clear();
    switch(CurrentAuton) {
        case Null:
            break;

        case RunRightQual:
            RightQual();
            break;

        case RunLeftQual:
            LeftQual();
            break;

        case RunRightElim:
            RightElim();
            break;

        case RunLeftElim:
            LeftElim();
            break;

        case RunSoloAWP:
            SoloAWP();
            break;

        case RunAutonSkills:
            AutonSkills();
            break;
    }
    std::cout << autonTimer.time(msec) << std::endl;
}

void driverControl() {
    if(!RunningPreAuton) {
        while(true) {
            if(pressed(Controller.ButtonA, A)) {
                descore_middleGoal();
            }
            if(pressed(Controller.ButtonX, X)) {
                matchload();
            }
            if(pressed(Controller.ButtonLeft, Left)) {
                doublePark();
            }
            moveIntake();
            moveDrivetrain();
            wait(20, msec);
        }
    }
}

int main() {
    //rotationTest2(10);
    //rotationTest(200);
    Matchloader.set(true);

    Competition.drivercontrol(driverControl); // If switch is in Driver Control run DriverControl
    Competition.autonomous(autonomous); // If switch is autonomous run autonomous

    preAuton(); // Calibrate Inertial sensor, select auton, select driver

    while(true) {
        wait(20, msec);
    }
}
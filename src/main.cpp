#include "vex.h"
#include "autons.h"
#include "auton-selector.h"
#include "driver-control.h"
#include "pressed.h"
#include <iostream>

competition Competition;

Drivetrain chassis(Brain, LeftDrive, RightDrive, Inertial, 1, 4);

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
    
    vexcodeInit();
}

void autonomous() {
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
}

void driverControl() {
    if(!RunningPreAuton) {
        while(true) {
            /*if(pressed(Controller.ButtonA, A)) {
                descore_middleGoal();
            }
            if(pressed(Controller.ButtonX, X)) {
                matchload();
            }
            if(pressed(Controller.ButtonLeft, Left)) {
                doublePark();
            }*/
            moveIntake();
            moveDrivetrain();
            wait(20, msec);
        }
    }
}

int main() {
    preAuton(); // Calibrate Inertial sensor, select auton, select driver
    Competition.drivercontrol(driverControl); // If switch is in Driver Control run DriverControl
    Competition.autonomous(autonomous); // If switch is autonomosu run autonomous

    while(true) {
        wait(20, msec);
    }
}
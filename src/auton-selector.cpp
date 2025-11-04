#include "auton-selector.h"

void displayAuton() {
    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(1, 1);
    switch(CurrentAuton) {
        case Null:
            Controller.Screen.print("No Auton Selected");
            break;

        case RunRightQual:
            Controller.Screen.print("Right Qual");
            break;

        case RunLeftQual:
            Controller.Screen.print("Left Qual");
            break;

        case RunRightElim:
            Controller.Screen.print("Right Elim");
            break;

        case RunLeftElim:
            Controller.Screen.print("Left Elim");
            break;

        case RunSoloAWP:
            Controller.Screen.print("Solo AWP");
            break;

        case RunAutonSkills:
            Controller.Screen.print("Auton Skills");
            break;
    }
}

void changeAutonRight() {
    displayAuton();
    switch(CurrentAuton) {
        case Null:
            CurrentAuton = RunRightQual;
            displayAuton();
            break;

        case RunRightQual:
            CurrentAuton = RunLeftQual;
            displayAuton();
            break;

        case RunLeftQual:
            CurrentAuton = RunRightElim;
            displayAuton();
            break;

        case RunRightElim:
            CurrentAuton = RunLeftElim;
            displayAuton();
            break;

        case RunLeftElim:
            CurrentAuton = RunSoloAWP;
            displayAuton();
            break;

        case RunSoloAWP:
            CurrentAuton = RunAutonSkills;
            displayAuton();
            break;

        case RunAutonSkills:
            CurrentAuton = Null;
            displayAuton();
            break;
    }
}

void changeAutonLeft() {
    displayAuton();
    switch(CurrentAuton) {
        case Null:
            CurrentAuton = RunAutonSkills;
            displayAuton();
            break;

        case RunRightQual:
            CurrentAuton = Null;
            displayAuton();
            break;

        case RunLeftQual:
            CurrentAuton = RunRightQual;
            displayAuton();
            break;

        case RunRightElim:
            CurrentAuton = RunLeftQual;
            displayAuton();
            break;

        case RunLeftElim:
            CurrentAuton = RunRightElim;
            displayAuton();
            break;

        case RunSoloAWP:
            CurrentAuton = RunLeftElim;
            displayAuton();
            break;

        case RunAutonSkills:
            CurrentAuton = RunSoloAWP;
            displayAuton();
            break;
    }
}

void ifAutonButtonPressed() {
    AutonButtonPressed = true;
}
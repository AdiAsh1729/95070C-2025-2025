#pragma once

#include "vex.h"
#include "robot-config.h"
#include <iostream>
using namespace vex;

inline bool RunningPreAuton = true;
inline bool RunningAuton = true;

enum Auton {
    Null,
    RunRightQual,
    RunLeftQual,
    RunRightElim,
    RunLeftElim,
    RunSoloAWP,
    RunAutonSkills
};

inline Auton CurrentAuton = Null;
inline bool AutonButtonPressed = false;

void displayAuton();
void changeAutonRight();
void changeAutonLeft();
void ifAutonButtonPressed();
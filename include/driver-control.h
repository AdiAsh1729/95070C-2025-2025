#pragma once

#include "vex.h"
#include "driver-selector.h"
#include "PID.h"
#include "pressed.h"
#include "robot-config.h"
#include "util.h"
using namespace vex;

inline int DMPressed = 0;
inline int MatchloadPressed = 0;
inline int ParkPressed = 0;

void runIfPressingMotor(motor&, controller::button&, controller::button&, int);
void runIfPressingMotorGroup(motor_group&, controller::button&, controller::button&, int);
void runIfPressedMotor(motor&, controller::button&, controller::button&, controller::button&, int);
void runIfPressedMotorGroup(motor_group&, controller::button&, controller::button&, controller::button&, int);
void runArcadeDrive(motor_group&, motor_group&, inertial&, controller&);
void rotationTest(double RPM);
void rotationTest2(double velocity);

void descore_middleGoal();
void matchload();
void doublePark();
void moveIntake();
void moveDrivetrain();
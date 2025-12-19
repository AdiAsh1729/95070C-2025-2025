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

void runIfPressingMotor(motor&, const controller::button&, const controller::button&, int, int);
void runIfPressingMotorGroup(motor_group&, const controller::button&, const controller::button&, int, int);
void runIfPressedMotor(motor&, const controller::button&, const controller::button&, const controller::button&, int, int);
void runIfPressedMotorGroup(motor_group&, const controller::button&, const controller::button&, const controller::button&, int, int);
void runArcadeDrive(motor_group&, motor_group&, controller&, const controller::button&, double, double);
void rotationTest(double RPM);
void rotationTest2(double velocity);

void descore_middleGoal();
void matchload();
void doublePark();
void moveIntake();
void moveDrivetrain();
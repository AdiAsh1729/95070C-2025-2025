#pragma once

#include "vex.h"
using namespace vex;
using signature = vision::signature;
using code = vision::code;

extern brain Brain;
extern controller Controller;

extern motor FL;
extern motor ML;
extern motor BL;
extern motor_group LeftDrive;
extern motor FR;
extern motor MR;
extern motor BR;
extern motor_group RightDrive;

extern inertial Inertial;

extern rotation HorizontalTracker;

extern motor Intake1;
extern motor Intake2;
extern motor_group Intake;

extern digital_out Descore_MiddleGoal;
extern digital_out Matchloader;
extern digital_out Park;

void vexcodeInit(void);
#include "robot-config.h"

brain Brain; //our brain
controller Controller = controller(primary); //our controller

motor FL = motor(PORT13, ratio6_1, true); //our front left motor
motor ML = motor(PORT11, ratio6_1, true); //our middle left motor
motor BL = motor(PORT12, ratio6_1, true); //our back left motor
motor_group LeftDrive = motor_group(FL, ML, BL); //a motor group consisting of the motors on the left side of our drivetrain
motor FR = motor(PORT17, ratio6_1, false); //our front right motor
motor MR = motor(PORT20, ratio6_1, false); //our middle right motor
motor BR = motor(PORT19, ratio6_1, false); //our back right motor
motor_group RightDrive = motor_group(FR, MR, BR); //a motor group consisting of the motors on the right side of our drivetrain

motor Intake1 = motor(PORT7, ratio6_1, false); //the motor controlling our first stage intake
motor Intake2 = motor(PORT5, ratio6_1, true); //the motor controlling our second stage intake
motor_group Intake = motor_group(Intake1, Intake2); //the motor group consisting of the motors controlling our intake

digital_out Descore_MiddleGoal = digital_out(Brain.ThreeWirePort.G); //the pneumatics controlling both our bunny ears mech and our middle goal scoring mech simultaneously
digital_out Matchloader = digital_out(Brain.ThreeWirePort.A); //the pneumatics controlling our matchloader
digital_out Park = digital_out(Brain.ThreeWirePort.H); //the pneumatics controlling our double park mechanism

inertial Inertial = inertial(PORT16); //our inertial sensor
<<<<<<< HEAD
=======

//Port 6 is saved for DummyRotation
>>>>>>> 2597543d00a13b769a7d9a7e46102094d7318bb8

void vexcodeInit(void) {

} 
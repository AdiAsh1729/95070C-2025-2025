#include "robot-config.h"

brain Brain; //our brain
controller Controller = controller(primary); //our controller

motor FL = motor(PORT20, ratio18_1, false); //our front left motor
motor BL = motor(PORT15, ratio18_1, false); //our back left motor
motor_group LeftDrive = motor_group(FL, BL); //a motor group consisting of the motors on the left side of our drivetrain
motor FR = motor(PORT6, ratio18_1, true); //our front right motor
motor BR = motor(PORT12, ratio18_1, true); //our back right motor
motor_group RightDrive = motor_group(FR, BR); //a motor group consisting of the motors on the right side of our drivetrain

inertial Inertial = inertial(PORT16); //our inertial sensor

rotation HorizontalTracker = rotation(PORT14, true);

//NOT BEING USED
motor Intake1 = motor(PORT2, ratio6_1, false); //the motor controlling our first stage intake
motor Intake2 = motor(PORT3, ratio6_1, true); //the motor controlling our second stage intake
motor_group Intake = motor_group(Intake1, Intake2); //the motor group consisting of the motors controlling our intake

digital_out Descore_MiddleGoal = digital_out(Brain.ThreeWirePort.A); //the pneumatics controlling both our bunny ears mech and our middle goal scoring mech simultaneously
digital_out Matchloader = digital_out(Brain.ThreeWirePort.B); //the pneumatics controlling our matchloader
digital_out Park = digital_out(Brain.ThreeWirePort.C); //the pneumatics controlling our double park mechanism
//NOT BEING USED

void vexcodeInit(void) {

} 
#include "autons.h"

void SetPIDConstants() {
    //chassis.driveDistanceConstants.kp = 3.5; chassis.driveDistanceConstants.ki = 0.001; chassis.driveDistanceConstants.kd = 0.2;
    chassis.driveDistanceConstants.kp = 3.5; chassis.driveDistanceConstants.ki = 0.001; chassis.driveDistanceConstants.kd = 0;
    
    //chassis.driveDistanceSlowConstants.kp = 1.25; chassis.driveDistanceSlowConstants.ki = 0.001; chassis.driveDistanceSlowConstants.kd = 0.65;
    chassis.driveDistanceSlowConstants.kp = 1.25; chassis.driveDistanceSlowConstants.ki = 0.049; chassis.driveDistanceSlowConstants.kd = 0.5;

    chassis.turnToHeadingConstants.kp = 0.3; chassis.turnToHeadingConstants.ki = 0.001; chassis.turnToHeadingConstants.kd = 0;
}

void oscillate(motor_group& MotorGroup, int numberOfOscillations, double speedOfOscillation, double timeOfOscillation) {
    for(int i = 0; i < numberOfOscillations; i++) {
        MotorGroup.spin(forward, speedOfOscillation, pct);
        wait(timeOfOscillation, msec);
        MotorGroup.spin(reverse, speedOfOscillation, pct);
        if(i < numberOfOscillations - 1) {
            wait(timeOfOscillation, msec);
        }
    }
}

void RightQual() {
    std::cout << "RightQual started" << std::endl;
    SetPIDConstants();

    Intake.setVelocity(99, pct);
    Descore_MiddleGoal.set(true);
    Intake1.spin(forward);
    wait(50, msec);
    chassis.driveDistance(15);
    wait(50, msec);
    chassis.driveDistanceSlow(10);
    wait(50, msec);
    chassis.turnToHeading(87.5);
    wait(50, msec);
    chassis.driveDistance(27.75);
    wait(50, msec);
    chassis.turnToHeading(170);
    wait(50, msec);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(310, msec);
    LeftDrive.spin(reverse, 10, pct);
    RightDrive.spin(reverse, 10, pct);
    Matchloader.set(false);
    Intake.spin(forward);
    
    wait(250, msec);
    LeftDrive.stop();
    RightDrive.stop();
    wait(1000, msec);
    Intake2.stop();
    LeftDrive.spin(forward, 90, pct);
    RightDrive.spin(forward, 90, pct);
    wait(390, msec);
    LeftDrive.spin(forward, 30, pct);
    RightDrive.spin(forward, 30, pct);
    wait(2, sec);

    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(100, msec);
    chassis.turnToHeading(165);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(1000, msec);
    LeftDrive.stop();
    RightDrive.stop();
    oscillate(Intake, 1, 99, 500);
    Intake.spin(forward);
}

void LeftQual() {
    std::cout << "LeftQual started!" << std::endl;
    SetPIDConstants();

    Intake.setVelocity(99, pct);
    Descore_MiddleGoal.set(true);
    Intake1.spin(forward);
    wait(50, msec);
    chassis.driveDistance(15);
    wait(50, msec);
    chassis.driveDistanceSlow(10);
    wait(50, msec);
    chassis.turnToHeading(272.5);
    wait(50, msec);
    chassis.driveDistance(27.75);
    wait(50, msec);
    chassis.turnToHeading(190);
    wait(50, msec);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(310, msec);
    LeftDrive.spin(reverse, 10, pct);
    RightDrive.spin(reverse, 10, pct);
    Matchloader.set(false);
    Intake.spin(forward);
    
    wait(250, msec);
    LeftDrive.stop();
    RightDrive.stop();
    wait(1000, msec);
    Intake2.stop();
    LeftDrive.spin(forward, 90, pct);
    RightDrive.spin(forward, 90, pct);
    wait(390, msec);
    LeftDrive.spin(forward, 30, pct);
    RightDrive.spin(forward, 30, pct);
    wait(2, sec);

    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(100, msec);
    chassis.turnToHeading(195);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(1000, msec);
    LeftDrive.stop();
    RightDrive.stop();
    oscillate(Intake, 1, 99, 500);
    Intake.spin(forward);
}

void RightElim() {
    chassis.driveDistance(1);
}

void LeftElim() {
<<<<<<< HEAD
    chassis.turnToHeading(180);
}

void SoloAWP() {
    chassis.driveDistance(48);
=======
    
}

void SoloAWP() {
    std::cout << "SoloAWP started" << std::endl;
    SetPIDConstants();

    Inertial.setHeading(165, deg);
    chassis.driveDistance(27);
    wait(50, msec);
    chassis.turnToHeading(80);
    LeftDrive.spin(forward, 75, pct);
    RightDrive.spin(forward, 75, pct);
    wait(1500, msec);
    LeftDrive.stop();
    RightDrive.stop();
>>>>>>> 2597543d00a13b769a7d9a7e46102094d7318bb8
}

void AutonSkills() {
    std::cout << "AutonSkills started" << std::endl;
    SetPIDConstants();

    /*Intake.setVelocity(99, pct);
    Descore_MiddleGoal.set(true);
    Intake1.spin(forward);
    wait(50, msec);
    chassis.driveDistance(15);
    wait(50, msec);
    chassis.driveDistanceSlow(10);
    wait(50, msec);
    chassis.turnToHeading(87.5);
    wait(50, msec);
    chassis.driveDistance(29.75);
    wait(50, msec);
    chassis.turnToHeading(165);
    wait(50, msec);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(200, msec);
    LeftDrive.spin(reverse, 10, pct);
    RightDrive.spin(reverse, 10, pct);
    Matchloader.set(false);
    Intake.spin(forward);
    
    wait(500, msec);
    LeftDrive.stop();
    RightDrive.stop();
    wait(1000, msec);
    Intake2.stop();
    LeftDrive.spin(forward, 90, pct);
    RightDrive.spin(forward, 90, pct);
    wait(490, msec);
    LeftDrive.spin(forward, 30, pct);
    RightDrive.spin(forward, 30, pct);
    wait(600, msec);
    chassis.oscillate(4, 10, 400);

    wait(1000, msec);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(50, msec);
    chassis.turnToHeading(165);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(2, sec);
    LeftDrive.stop();
    RightDrive.stop();
    Intake.spin(forward);
    wait(2, sec);
    oscillate(Intake, 2, 99, 500);
    Intake.spin(forward);
    wait(500, msec);
    Inertial.setHeading(165, deg);
    Intake.stop();
    Matchloader.set(true);
    //////////////////////////////////////////////////
    
    wait(50, msec);
    chassis.driveDistance(20);
    wait(50, msec);
    chassis.turnToHeading(255);
    wait(50, msec);
    chassis.driveDistance(73);
    wait(50, msec);
    chassis.turnToHeading(345);
    wait(50, msec);
    Intake1.spin(forward);
    chassis.driveDistanceSlow(20);
    //////////////////////////////////////////////////

    chassis.turnToHeading(212.5);
    wait(50, msec);
    chassis.driveDistance(29.75);
    wait(50, msec);
    chassis.turnToHeading(165);
    wait(50, msec);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(400, msec);
    LeftDrive.spin(reverse, 10, pct);
    RightDrive.spin(reverse, 10, pct);
    Matchloader.set(false);
    Intake.spin(forward);
    
    wait(500, msec);
    LeftDrive.stop();
    RightDrive.stop();
    wait(1000, msec);
    Intake2.stop();
    LeftDrive.spin(forward, 90, pct);
    RightDrive.spin(forward, 90, pct);
    wait(490, msec);
    LeftDrive.spin(forward, 30, pct);
    RightDrive.spin(forward, 30, pct);
    wait(600, msec);
    chassis.oscillate(4, 10, 400);

    wait(1000, msec);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(50, msec);
    chassis.turnToHeading(165);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(2, sec);
    LeftDrive.stop();
    RightDrive.stop();
    Intake.spin(forward);
    wait(2, sec);
    oscillate(Intake, 2, 99, 500);
    Intake.spin(forward);
    wait(3, sec);
    Intake.stop();
    Matchloader.set(true);
    //////////////////////////////////////////////////
    
    Inertial.setHeading(165, deg);
    chassis.driveDistance(27);
    wait(50, msec);
    chassis.turnToHeading(80);
    LeftDrive.spin(forward, 75, pct);
    RightDrive.spin(forward, 75, pct);
    wait(1500, msec);
    LeftDrive.stop();
    RightDrive.stop();*/

    /*chassis.driveDistance(-6);
    Matchloader.set(false);
    LeftDrive.spin(forward, 90, pct);
    RightDrive.spin(forward, 90, pct);
    wait(1.1, sec);
    LeftDrive.stop();
    RightDrive.stop();
    Matchloader.set(true);*/

    chassis.driveDistanceSlow(48);
}
#include "autons.h"

void SetPIDConstants() {
    chassis.driveDistanceConstants.kp = 3.6; chassis.driveDistanceConstants.ki = 0; chassis.driveDistanceConstants.kd = 0.3;

    //chassis.driveDistanceSlowConstants.kp = 0.75; chassis.driveDistanceSlowConstants.ki = 0.05; chassis.driveDistanceSlowConstants.kd = 0.5;
    chassis.driveDistanceSlowConstants.kp = 1.25; chassis.driveDistanceSlowConstants.ki = 0.05; chassis.driveDistanceSlowConstants.kd = 0.5;

    chassis.turnToHeadingConstants.kp = 0.34; chassis.turnToHeadingConstants.ki = 0; chassis.turnToHeadingConstants.kd = 0.25;
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
    chassis.driveDistance(30);
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
    LeftDrive.spin(forward, 30, pct);
    RightDrive.spin(forward, 30, pct);
    wait(1750, msec);
    chassis.oscillate(3, 90, 300);

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
    //LeftDrive.spin(forward, 30, pct);
    //RightDrive.spin(forward, 30, pct);
}

void LeftQual() {
    std::cout << "LeftQual started!" << std::endl;
    SetPIDConstants();
    
    /*Intake.setVelocity(99, pct);
    Descore_MiddleGoal.set(true);
    Intake1.spin(forward);
    wait(50, msec);
    chassis.driveDistanceSlow(30);
    wait(50, msec);
    Intake.stop();
    chassis.turnToHeading(250);
    wait(50, msec);
    chassis.driveDistance(32.75);
    wait(50, msec);
    chassis.turnToHeading(195);
    wait(50, msec);
    LeftDrive.spin(reverse, 90, pct);
    RightDrive.spin(reverse, 90, pct);
    wait(500, msec);
    LeftDrive.stop();
    RightDrive.stop();
    Intake.spin(forward);*/

    chassis.driveDistanceSlow(48);
}

void RightElim() {
    std::cout << "RightElim started!" << std::endl;
    SetPIDConstants();
    
    /*Intake.setVelocity(99, pct);
    Descore_MiddleGoal.set(true);
    chassis.driveDistance(-40);
    wait(50, msec);
    Intake.spin(forward);
    wait(250, msec);
    Intake.stop();
    chassis.driveDistance(15);
    chassis.turnToHeading(300);
    wait(50, msec);
    chassis.driveDistanceSlow(24);
    wait(50, msec);
    chassis.turnToHeading(165);
    wait(50, msec);
    LeftDrive.spin(reverse, 90, pct);
    RightDrive.spin(reverse, 90, pct);
    wait(250, msec);
    LeftDrive.stop();
    RightDrive.stop();
    Intake.spin(forward);*/
}

void LeftElim() {
    
}

void SoloAWP() {
    
}

void AutonSkills() {
    /*Matchloader.set(false);
    chassis.driveDistance(36);
    chassis.turnToHeading(270);
    Matchloader.set(true);
    Intake.spin(forward);
    chassis.driveDistanceSlow(8);
    wait(10, sec);
    chassis.driveDistanceSlow(-8);
    chassis.turnToHeading(0);
    chassis.driveDistance(36);*/
    /*chassis.driveDistance(-6);
    Matchloader.set(true);
    LeftDrive.spin(forward, 90, pct);
    RightDrive.spin(forward, 90, pct);
    wait(1.4, sec);
    LeftDrive.stop();
    RightDrive.stop();
    Matchloader.set(false);*/
}
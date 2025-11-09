#include "autons.h"

void RightQual() {
    /*std::cout << "RightQual started" << std::endl;
    Intake.setVelocity(99, pct);
    Descore_MiddleGoal.set(true);
    Intake1.spin(forward);
    wait(50, msec);
    chassis.driveDistanceSlow(30);
    wait(50, msec);
    chassis.turnToHeading(295);
    Intake.stop();
    wait(50, msec);
    chassis.driveDistance(8.5);
    wait(50, msec);
    Intake.spin(reverse);
    wait(1, sec);
    Intake1.spin(forward);
    wait(500, msec);
    Intake1.spin(reverse);
    wait(1, sec);
    Intake1.spin(forward);
    wait(500, msec);
    Intake.spin(reverse);*/
    /*Intake.setVelocity(99, pct);
    Descore_MiddleGoal.set(true);
    Intake1.spin(forward);
    wait(50, msec);
    chassis.driveDistanceSlow(30);
    wait(50, msec);
    chassis.turnToHeading(295);
    Intake.stop();
    wait(50, msec);
    chassis.driveDistance(12);
    wait(50, msec);
    Intake.spin(reverse);
    wait(1, sec);
    Intake1.spin(forward);
    wait(500, msec);
    Intake1.spin(reverse);
    wait(1, sec);
    Intake1.spin(forward);
    wait(500, msec);*/
    std::cout << "RightQual started" << std::endl;
    Intake.setVelocity(99, pct);
    Descore_MiddleGoal.set(true);
    Intake1.spin(forward);
    wait(50, msec);
    chassis.driveDistanceSlow(30);
    wait(50, msec);
    Intake.stop();
    chassis.turnToHeading(110);
    wait(50, msec);
    chassis.driveDistance(33.5);
    wait(50, msec);
    chassis.turnToHeading(165);
    wait(50, msec);
    LeftDrive.spin(reverse, 90, pct);
    RightDrive.spin(reverse, 90, pct);
    wait(400, msec);
    LeftDrive.stop();
    RightDrive.stop();
    Intake.spin(forward);
}

void LeftQual() {
    std::cout << "LeftQual started" << std::endl;
    Intake.setVelocity(99, pct);
    Descore_MiddleGoal.set(true);
    Intake1.spin(forward);
    wait(50, msec);
    chassis.driveDistanceSlow(30);
    wait(50, msec);
    Intake.stop();
    chassis.turnToHeading(250);
    wait(50, msec);
    chassis.driveDistance(33.5);
    wait(50, msec);
    chassis.turnToHeading(195);
    wait(50, msec);
    LeftDrive.spin(reverse, 90, pct);
    RightDrive.spin(reverse, 90, pct);
    wait(400, msec);
    LeftDrive.stop();
    RightDrive.stop();
    Intake.spin(forward);
}

void RightElim() {

}

void LeftElim() {

}

void SoloAWP() {
    chassis.driveDistance(48);
}

void AutonSkills() {
    chassis.driveDistance(-6);
    Matchloader.set(true);
    LeftDrive.spin(forward, 90, pct);
    RightDrive.spin(forward, 90, pct);
    wait(1.4, sec);
    LeftDrive.stop();
    RightDrive.stop();
    Matchloader.set(false);
}
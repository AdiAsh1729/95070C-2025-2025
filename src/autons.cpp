#include "autons.h"

void SetPIDConstants() {
    chassis.driveDistanceConstants.kp = 3.6; chassis.driveDistanceConstants.ki = 0; chassis.driveDistanceConstants.kd = 0.3;

    //chassis.driveDistanceSlowConstants.kp = 0.75; chassis.driveDistanceSlowConstants.ki = 0.05; chassis.driveDistanceSlowConstants.kd = 0.5;
    chassis.driveDistanceSlowConstants.kp = 1.25; chassis.driveDistanceSlowConstants.ki = 0.05; chassis.driveDistanceSlowConstants.kd = 0.5;

    chassis.turnToHeadingConstants.kp = 0.34; chassis.turnToHeadingConstants.ki = 0; chassis.turnToHeadingConstants.kd = 0.25;
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
    chassis.driveDistance(30.5);
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
    
    wait(250, msec);
    LeftDrive.stop();
    RightDrive.stop();
    wait(1000, msec);
    Intake2.stop();
    LeftDrive.spin(forward, 90, pct);
    RightDrive.spin(forward, 90, pct);
    wait(480, msec);
    LeftDrive.spin(forward, 30, pct);
    RightDrive.spin(forward, 30, pct);
    wait(400, msec);
    chassis.oscillate(3, 10, 300);

    wait(500, msec);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(50, msec);
    chassis.turnToHeading(165);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(2, sec);
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
    chassis.driveDistance(30.5);
    wait(50, msec);
    chassis.turnToHeading(195);
    wait(50, msec);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(200, msec);
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
    wait(480, msec);
    LeftDrive.spin(forward, 30, pct);
    RightDrive.spin(forward, 30, pct);
    wait(400, msec);
    chassis.oscillate(3, 10, 300);

    wait(500, msec);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(50, msec);
    chassis.turnToHeading(195);
    LeftDrive.spin(reverse, 50, pct);
    RightDrive.spin(reverse, 50, pct);
    wait(2, sec);
    LeftDrive.stop();
    RightDrive.stop();
    oscillate(Intake, 1, 99, 500);
    Intake.spin(forward);
}

void RightElim() {
    
}

void LeftElim() {
    
}

void SoloAWP() {
    std::cout << "SoloAWP started" << std::endl;
    SetPIDConstants();

    Inertial.setHeading(165, deg);
    chassis.driveDistancePct(27);
    wait(50, msec);
    chassis.turnToHeading(80);
    LeftDrive.spin(forward, 75, pct);
    RightDrive.spin(forward, 75, pct);
    wait(1500, msec);
    LeftDrive.stop();
    RightDrive.stop();
}

void AutonSkills() {
    std::cout << "AutonSkills started" << std::endl;
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
    chassis.driveDistance(29);
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
    wait(500, msec);
    chassis.oscillate(3, 10, 400);

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
    chassis.driveDistancePct(20);
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
    wait(500, msec);
    chassis.oscillate(3, 10, 400);

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
    chassis.driveDistancePct(27);
    wait(50, msec);
    chassis.turnToHeading(80);
    LeftDrive.spin(forward, 75, pct);
    RightDrive.spin(forward, 75, pct);
    wait(1500, msec);
    LeftDrive.stop();
    RightDrive.stop();
}
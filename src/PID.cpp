#include "PID.h"

PID::PID(double startError, double error, double kp, double ki, double kd, double ks, double startIntegral, double integral, double derivative, double previousError, double deadband, double previousMotorOutput, double motorOutput):
    startError(startError),
    error(error),
    kp(kp),
    ki(ki),
    kd(kd),
    ks(ks),
    startIntegral(startIntegral),
    integral(integral),
    derivative(derivative),
    previousError(previousError),
    deadband(deadband),
    previousMotorOutput(previousMotorOutput),
    motorOutput(motorOutput)
{};

void PID::print() {
    std::cout << this->error << ", " << this->motorOutput << ", " << this->previousError << ", " << this->previousMotorOutput << std::endl;
}

bool PID::settled() {
    if((std::abs(this->error) < deadband)) { //checks if the absolute value of the error is less than the deadband: in other words, it checks if the robot is close enough
        return true;
    }

    else {
        return false;
    }
};

double PID::output() {
    this->derivative = (this->previousError - this->error) * 50;
    
    if(std::abs(this->error) < this->startIntegral) {
        this->integral += (this->error)/50;
    }

    if(getSign(this->error) != getSign(this->startError)) {
        this->integral = 0;
    }

    this->previousError = this->error;

    this->motorOutput = this->error * this->kp + this->integral * this->ki + this->derivative * this->kd + getSign(this->error) * this->ks;

    this->previousMotorOutput = this->motorOutput;

    if(std::abs(this->motorOutput) > 99.9) {
        return getSign(this->motorOutput) * 99.9;
    }

    else {
        return this->motorOutput;
    }    
};
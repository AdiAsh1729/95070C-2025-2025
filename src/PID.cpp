#include "PID.h"

PID::PID(double startError, double error, double kp, double ki, double kd, double startIntegral, double integral, double derivative, double previousError, double deadband, double motorOutput, double minimumMotorOutput, double timeout):
    startError(startError),
    error(error),
    kp(kp),
    ki(ki),
    kd(kd),
    startIntegral(startIntegral),
    integral(integral),
    derivative(derivative),
    previousError(previousError),
    deadband(deadband),
    motorOutput(motorOutput),
    minimumMotorOutput(minimumMotorOutput),
    timeout(timeout)
{};

bool PID::settled() {
    if((std::abs(this->error) < this->deadband)) { //checks if the absolute value of the error is less than the deadband: in other words, it checks if the robot is close enough
        return true;
    }

    else if(this->timeSpent > this->timeout) { //checks if the time the PID has spent is greater than our timeout
        return true;
    }

    else {
        return false;
    }
};

double PID::output() {
    this->derivative = this->error - this->previousError;

    //std::cout << "Derivative: " << this->derivative << std::endl;
    
    if(std::abs(this->error) < this->startIntegral) {
        this->integral += this->error;
    }

    if(getSign(this->error) != getSign(this->startError)) {
        this->integral = 0;
    }

    //std::cout << "Integral: " << this->integral << std::endl;

    this->previousError = this->error;

    this->motorOutput = this->error * this->kp + this->integral * this->ki + this->derivative * this->kd;

    //std::cout << "Motor output & clamped: " << this->motorOutput << ", " << clamp(this->motorOutput, this->minimumMotorOutput, 99.9) << std::endl;

    return clamp(this->motorOutput, getSign(this->startError) * this->minimumMotorOutput, getSign(this->startError) * 99.9);
};
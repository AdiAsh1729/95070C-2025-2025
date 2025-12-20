#include "PID.h"

PID::PID(double startError, double error, double kp, double ki, double kd, double startIntegral, double integral, double derivative, double previousError, double deadband, double motorOutput, IntegralMethod integralMethod):
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
    integralMethod(integralMethod)
{};

bool PID::settled() {
    return (std::abs(this->error) < deadband);
};

double PID::output() {
    this->derivative = (this->error - this->previousError) * 50;
    
    if(std::abs(this->error) < this->startIntegral) {
        this->integral += this->error / 50;
    }

    if(integralMethod == Reset) {
        if(getSign(this->error) != getSign(this->startError)) {
            this->integral = 0;
        }
    }

    this->previousError = this->error;

    return this->error * this->kp + this->integral * this->ki - this->derivative * this->kd; 
};
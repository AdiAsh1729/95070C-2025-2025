#pragma once

#include "util.h"
#include <cmath>
#include <iostream>

enum IntegralMethod {
    Decay,
    Reset
};

class PID {
    public:
        double startError; //error at the start of the PID
        double error; //current error
        double kp; //the constant we multiply our error by: we tune this
        double ki; //the constant we multiply our integral by: we tune this
        double kd; //the constant we multiply our derivative by: we tune this
        
        double startIntegral; //when we start adding on to our integral term
        double integral; //our integral term
        double derivative; //our derivative term
        double previousError; //our error in the previous loop

        double deadband; //how far off we can be from our target: we will never perfectly achieve our target, so we need this
        double motorOutput; //how fast our motors will spin this loop
        double minimumMotorOutput; //minimum speed our motors need to spin at
        IntegralMethod integralMethod;
        
        PID(double startError, double error, double kp, double ki, double kd, double startIntegral, double integral, double derivative, double previousError, double deadband, double motorOutput, IntegralMethod integralMethod); //our constructor, what we use to create our object

        bool settled(); //a function which returns true or false: if true, our PID is finished, otherwise our PID needs to keep on running
        double output(); //how fast our motors will spin this loop, function which returns our motor output
};

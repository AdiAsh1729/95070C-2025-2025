#pragma once

#include "vex.h"
#include <cmath>
#include <iostream>
using namespace vex;

double getSign(double input);
double getTurnError(double heading, double target);
double degreesToRadians(double degrees);
double radiansToDegrees(double radians);
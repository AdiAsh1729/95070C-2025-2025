#pragma once

#include "vex.h"
using namespace vex;

enum Button {
    A,
    B,
    X,
    Y,
    Right,
    Left,
    Up,
    Down,
    R1,
    R2,
    L1,
    L2
};

inline bool buttonStatePrevious[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
inline bool buttonStateCurrent[12] = {false, false, false, false, false, false, false, false, false, false, false, false};

bool pressed(const controller::button&, Button);
void resetPressed();
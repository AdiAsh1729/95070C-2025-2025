#include "pressed.h"

bool pressed(const controller::button& checkButton, Button checkButtonID) {
    buttonStatePrevious[checkButtonID] = buttonStateCurrent[checkButtonID];

    if(checkButton.pressing()) {
        buttonStateCurrent[checkButtonID] = true;
    }

    else {
        buttonStateCurrent[checkButtonID] = false;
    }

    if(!buttonStatePrevious[checkButtonID] && buttonStateCurrent[checkButtonID]) {
        return true;
    }

    else {
        return false;
    }
}

void resetPressed() {
    for(int i = 0; i < 12; i++) {
        buttonStatePrevious[i] = false;
        buttonStateCurrent[i] = false;
    }
}
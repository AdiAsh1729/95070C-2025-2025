#include "driver-selector.h"

void displayDriver() {
    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(1, 1);
    switch(CurrentDriver) {
        case Daniel:
            Controller.Screen.print("Daniel");
            break;

        case Thomas:
            Controller.Screen.print("Thomas");
            break;

        case Nikhil:
            Controller.Screen.print("Nikhil");
            break;

        case Shaurya:
            Controller.Screen.print("Shaurya");
            break;

        case Noob:
            Controller.Screen.print("Noob");
            break;
    }
}

void changeDriverRight() {
    displayDriver();
    switch(CurrentDriver) {
        case Daniel:
            CurrentDriver = Thomas;
            displayDriver();
            break;

        case Thomas:
            CurrentDriver = Nikhil;
            displayDriver();
            break;

        case Nikhil:
            CurrentDriver = Shaurya;
            displayDriver();
            break;

        case Shaurya:
            CurrentDriver = Noob;
            displayDriver();
            break;

        case Noob:
            CurrentDriver = Daniel;
            displayDriver();
            break;
    }
}

void changeDriverLeft() {
    displayDriver();
    switch(CurrentDriver) {
        case Daniel:
            CurrentDriver = Noob;
            displayDriver();
            break;

        case Thomas:
            CurrentDriver = Daniel;
            displayDriver();
            break;

        case Nikhil:
            CurrentDriver = Thomas;
            displayDriver();
            break;

        case Shaurya:
            CurrentDriver = Nikhil;
            displayDriver();
            break;

        case Noob:
            CurrentDriver = Shaurya;
            displayDriver();
            break;
    }
}

void ifDriverButtonPressed() {
    DriverButtonPressed = true;
}
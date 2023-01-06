#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <limits>
#include "FileHandler.h"
#include "User.h"

using namespace std;

void getUserr() {
    int x;
    while (true) {
        cout << "Select user - (1) for nurse, (2) for doctor, (3) for hospital admin, (4) for sys admin:";
        cin >> x;
        if (cin.fail() || x < 1 || x > 4) {  // input is not valid
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid entry\n";
        } else break;
    }
    switch (x) {
        case 1:
            cout << "Logged in as nurse";
            Nurse n();
            break;
        case 2:
            cout << "Logged in as doctor";
            break;
        case 3:
            cout << "Logged in as hospital admin";
            break;
        case 4:
            cout << "Logged in as sys admin";
            break;
    }
}

#endif

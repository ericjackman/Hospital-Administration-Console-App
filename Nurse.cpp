// Eric Jackman, CSC 402 - Hospital Administration Console App

#include "User.h"

Nurse::Nurse(vector<Patient> *allPatients, priority_queue<Patient, vector<Patient>,
        greater<>> *waitingPatients) : User(allPatients, waitingPatients) {
    commands.insert(pair<string, string>("ADDPATIENT", "Adds new patient to system with user-prompted information"));
}

void Nurse::getCommand() {
    while (true) {  // loop until sign out command is called

        // Get input from user
        string in;
        while (true) {  // input validation
            cout << "\nC:\\Users\\Nurse>";
            cin >> in;
            transform(in.begin(), in.end(), in.begin(),
                      ::toupper);  // converts string to uppercase so commands are case insensitive for user
            if (cin.fail() || commands.find(in) == commands.end()) {  // input is not valid
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid command, type HELP for a list of commands\n";
            } else break;
        }

        // Process input
        if (in == "SIGNOUT")
            break;
        else if (in == "HELP")
            help();
        else if (in == "PRINTALL")
            outputPatients();
        else if (in == "ADDPATIENT")
            addPatient();
    }
}

// Prompts the user to enter patient information and then adds the new patient to containers
void Nurse::addPatient() {
    string in, fName, mName, lName, suffix, doctor;
    int in2, treated, priority;
    vector<string> ailments;

    // Get first name from user
    while (true) {  // input validation
        cout << "Enter patient's first name:";
        cin >> in;
        if (cin.fail()) {  // input is not valid
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
        } else break;
    }
    fName = in;

    // Get middle name from user
    while (true) {  // input validation
        cout << "Enter patient's middle name:";
        cin >> in;
        if (cin.fail()) {  // input is not valid
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
        } else break;
    }
    mName = in;

    // Get last name from user
    while (true) {  // input validation
        cout << "Enter patient's last name:";
        cin >> in;
        if (cin.fail()) {  // input is not valid
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
        } else break;
    }
    lName = in;

    // Get suffix from user
    while (true) {  // input validation
        cout << "Enter patient's suffix (or N/A):";
        cin >> in;
        if (cin.fail()) {  // input is not valid
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
        } else break;
    }
    if (in == "N/A" || in == "n/a")
        suffix = "";
    else
        suffix = in;

    // Get number of ailments from user
    while (true) {  // input validation
        cout << "Enter patient's number of ailments:";
        cin >> in2;
        if (cin.fail() || in2 <= 0 || in2 > 9) {  // input is not valid
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
        } else break;
    }
    int num = in2;

    // Get ailments from user
    for (int i = 1; i <= num; i++) {
        while (true) {  // input validation
            cout << "Enter ailment " << i << ":";
            cin.clear();
            cin.sync();
            getline(cin, in);
            if (cin.fail()) {  // input is not valid
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input\n";
            } else break;
        }
        ailments.push_back(in);
    }

    // Get doctor from user
    while (true) {  // input validation
        cout << "Enter patient's doctor:";
        cin.clear();
        cin.sync();
        getline(cin, in);
        if (cin.fail()) {  // input is not valid
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
        } else break;
    }
    doctor = in;

    // Get treated from user
    while (true) {  // input validation
        cout << "Enter (0) if the patient has not yet been treated or (1) if the patient has been treated:";
        cin >> in2;
        if (cin.fail() || (in2 != 0 && in2 != 1)) {  // input is not valid
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
        } else break;
    }
    treated = in2;

    // Get priority from user
    while (true) {  // input validation
        cout << "Enter patient's priority (1 - 9999):";
        cin >> in2;
        if (cin.fail() || in2 < 1 || in2 > 9999) {  // input is not valid
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
        } else break;
    }
    priority = in2;

    // Add new patient to list and waiting list
    Patient newPatient(fName, mName, lName, suffix, doctor, ailments, treated, priority);
    allPatients->emplace_back(newPatient);
    if (treated == 0)
        waitingPatients->push(newPatient);

    logCommand("Nurse added new patient \"" + newPatient.getFullName() + "\" to the system\n");
}

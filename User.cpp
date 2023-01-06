// Eric Jackman, CSC 402 - Hospital Administration Console App

#include "User.h"

User::User(vector<Patient> *allPatients, priority_queue<Patient, vector<Patient>,
        greater<>> *waitingPatients) : allPatients(allPatients), waitingPatients(waitingPatients) {
    commands.insert(pair<string, string>("SIGNOUT", "Signs the current user out and returns to sign-in prompt"));
    commands.insert(pair<string, string>("HELP", "List the available commands and gives a description of each"));
    commands.insert(pair<string, string>("PRINTALL", "Outputs a report of all patients"));
//    commands.insert(pair<string, string>("PRINTWAIT", "Outputs and clears waiting list"));
}

int User::debugMode = 0;

// Get input from the user and process input
void User::getCommand() {
    // Loop until user sign off
    while (true) {
        // Get input from user
        int in;
        while (true) {  // input validation
            cout << "\nSelect (1) for nurse, (2) for doctor, (3) for hospital admin, (4) for sys admin, "
                    "or (5) to sign off\n";
            cout << "C:\\Users>";
            cin >> in;
            if (cin.fail() || in < 1 || in > 5) {  // input is not valid
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "invalid entry\n";
            } else break;
        }

        // Process input
        if (in == 1) {
            Nurse n(allPatients, waitingPatients);
            logCommand("Nurse signed in\n");
            n.getCommand();
        } else if (in == 2) {
            Doctor d(allPatients, waitingPatients);
            logCommand("Doctor signed in\n");
            d.getCommand();
        } else if (in == 3) {
            HospAdmin h(allPatients, waitingPatients);
            logCommand("Hospital Admin signed in\n");
            h.getCommand();
        } else if (in == 4) {
            SysAdmin s(allPatients, waitingPatients);
            logCommand("System Admin signed in\n");
            s.getCommand();
        } else break;
    }
}

// Prints all patients to console
void User::outputPatients() {
    cout << "All records of patients:\n\n";
    vector<Patient>::const_iterator itr;
    for (itr = allPatients->begin(); itr != allPatients->end(); ++itr) {
        cout << itr->toString() << "\n";
    }

    logCommand("Report for all patients requested\n");
}

// Prints a list of commands and their descriptions that the user can use
void User::help() {
    cout << "The following commands are available:\n";
    map<string, string>::const_iterator itr;
    for (itr = commands.begin(); itr != commands.end(); ++itr) {
        cout << "  ";
        cout.width(12);
        cout << left << itr->first;
        cout << "\t\t" << itr->second << "\n";
    }

    logCommand("Command descriptions (help) requested\n");
}

// Creates a log of a command called from any user to hospital_system_log.txt and to the console if debug mode is on
void User::logCommand(const string &str) {
    // Create log of command
    fstream log("hospital_system_log.txt", ios::app);
    log << str;
    log.close();
    if (debugMode == 1)
        cout << "DEBUG: " << str;
}

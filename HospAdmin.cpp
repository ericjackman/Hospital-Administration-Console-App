// Eric Jackman, CSC 402 - Hospital Administration Console App

#include "User.h"

HospAdmin::HospAdmin(vector<Patient> *allPatients, priority_queue<Patient, vector<Patient>, greater<>> *waitingPatients)
        : User(allPatients, waitingPatients) {
    commands.insert(pair<string, string>("PRINTWAIT", "Outputs a report of all patients waiting to be treated"));
    commands.insert(pair<string, string>("TREATALL", "Treats all patients waiting in the system"));
    commands.insert(pair<string, string>("PRINTDOC", "Outputs a report of all patients assigned to a specific doctor"));
}

void HospAdmin::getCommand() {
    while (true) {  // loop until sign out command is called

        // Get input from user
        string in;
        while (true) {  // input validation
            cout << "\nC:\\Users\\HospAdmin>";
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
        else if (in == "PRINTWAIT")
            getWaitingPatients();
        else if (in == "TREATALL")
            treatAll();
        else if (in == "PRINTDOC")
            getByDoctor();
    }
}

// Prints all the patients that have not yet been treated to the console
void HospAdmin::getWaitingPatients() {
    cout << "The following are patients that have yet to be treated:\n\n";
    vector<Patient>::const_iterator itr;
    for (itr = allPatients->begin(); itr != allPatients->end(); ++itr) {
        if (itr->getTreated() == 0)
            cout << itr->toString() << "\n";
    }

    logCommand("Hospital Admin requested report of all untreated patients\n");
}

void HospAdmin::getByDoctor() {
    // Get name of doctor from user
    string name;
    cout << "Enter doctor's name:";
    cin.clear();
    cin.sync();
    getline(cin, name);

    int found = 0;
    cout << "The following are patients that have been assigned to Dr. " << name << ":\n\n";
    vector<Patient>::const_iterator itr;
    for (itr = allPatients->begin(); itr != allPatients->end(); ++itr) {
        if (itr->getDoctor() == name) {
            cout << itr->toString() << "\n";
            found = 1;
        }
    }

    if (found == 0)
        cout << "Dr. " << name << " currently has no patients\n";

    logCommand("Hospital Admin requested report of all patients assigned to Dr. " + name + "\n");
}

void HospAdmin::treatAll() {
    if (!waitingPatients->empty()) {
        while (!waitingPatients->empty()) {
            // Random wait time
            cout << "Treating patient...";
            int sleep = 1 + rand() % (3 - 1 + 1);
            this_thread::sleep_for(chrono::seconds(sleep));

            // Remove patient from waiting list
            string name = waitingPatients->top().getFullName();
            cout << name << " has been treated\n";
            waitingPatients->pop();

            // Set treated value of patient to 1
            vector<Patient>::iterator itr;
            for (itr = allPatients->begin(); itr != allPatients->end(); ++itr) {
                if (name == itr->getFullName()) {
                    itr->setTreated(1);
                    break;
                }
            }
        }
    } else cout << "There are no patients in the waiting list\n";

    cout << "All patients have been treated\n";
    logCommand("Hospital Admin treated all patients\n");
}

// Eric Jackman, CSC 402 - Hospital Administration Console App

#include "User.h"

Doctor::Doctor(vector<Patient> *allPatients, priority_queue<Patient, vector<Patient>, greater<>> *waitingPatients)
        : User(allPatients, waitingPatients) {
    commands.insert(pair<string, string>("GETNEXT", "Outputs the patient with the highest priority"));
    commands.insert(pair<string, string>("TREATNEXT", "Treats the patient with the highest priority"));
    commands.insert(pair<string, string>("GETREPORT", "Outputs a report of a specific patient"));
    commands.insert(pair<string, string>("PRINTTREATED", "Outputs a report of all treated patients"));
}

void Doctor::getCommand() {
    while (true) {  // loop until sign out command is called

        // Get input from user
        string in;
        while (true) {  // input validation
            cout << "\nC:\\Users\\Doctor>";
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
        else if (in == "GETNEXT")
            getNextPatient();
        else if (in == "TREATNEXT")
            treatNextPatient();
        else if (in == "GETREPORT")
            getReport();
        else if (in == "PRINTTREATED")
            printTreated();
    }
}

// Prints the next patient in the priority queue
void Doctor::getNextPatient() {
    if (!waitingPatients->empty())
        cout << waitingPatients->top().getFullName() << " is next up to be treated\n";
    else
        cout << "There are no patients in the waiting list\n";

    logCommand("Doctor checked the next patient to be treated\n");
}

// Pops the next patient from the priority queue and changes that patient's treated value
void Doctor::treatNextPatient() {
    if (!waitingPatients->empty()) {
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
        logCommand("Doctor treated patient " + name + "\n");

    } else cout << "There are no patients in the waiting list\n";
}

// Prompts the user to enter the name of a patient and then prints that patients data to the console
void Doctor::getReport() {
    // Get full name of patient from user
    string name;
    cout << "Enter patient's full name as \"Last, First M\":";
    cin.clear();
    cin.sync();
    getline(cin, name);

    // Search patients and print when found
    // Set treated value of patient to 1
    int found = 0;
    vector<Patient>::const_iterator itr;
    for (itr = allPatients->begin(); itr != allPatients->end(); ++itr) {
        if (name == itr->getFullName()) {
            found = 1;
            cout << "\n" << itr->toString() << "\n";
            break;
        }
    }

    if (found == 0)
        cout << name << " not found\n";

    logCommand("Doctor requested report of patient \"" + name + "\"\n");
}

// Prints all the patients that have already been treated to the console
void Doctor::printTreated() {
    cout << "The following are patients that have already been treated:\n\n";
    vector<Patient>::const_iterator itr;
    for (itr = allPatients->begin(); itr != allPatients->end(); ++itr) {
        if (itr->getTreated() == 1)
            cout << itr->toString() << "\n";
    }

    logCommand("Doctor requested report of all treated patients\n");
}

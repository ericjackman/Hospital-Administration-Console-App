// Eric Jackman, CSC 402 - Hospital Administration Console App

#include "User.h"

SysAdmin::SysAdmin(vector<Patient> *allPatients, priority_queue<Patient, vector<Patient>, greater<>> *waitingPatients)
        : User(allPatients, waitingPatients) {
    commands.insert(pair<string, string>("ADDBULK", "Add a file of patient records to the system"));
    commands.insert(pair<string, string>("TOGGLEDEBUG", "Turns on/off debug mode, which logs all users' commands"));
}

void SysAdmin::getCommand() {
    while (true) {  // loop until sign out command is called

        // Get input from user
        string in;
        while (true) {  // input validation
            cout << "\nC:\\Users\\SysAdmin>";
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
        else if (in == "ADDBULK")
            bulkAddPatients();
        else if (in == "TOGGLEDEBUG")
            toggleDebugMode();
    }
}

// Turns on/off debug mode for all users
void SysAdmin::toggleDebugMode() {
    if (debugMode == 0) {
        debugMode = 1;
        cout << "Debug mode is now on\n";
    } else {
        debugMode = 0;
        cout << "Debug mode is now off\n";
    }
}

// Prompts the user to enter a file and then inputs patient data from that file
void SysAdmin::bulkAddPatients() {
    // Get file name from user
    string file;
    cout << "Enter the name of the file to be imported:";
    cin.clear();
    cin.sync();
    getline(cin, file);

    // Input patients from file
    fstream addFile(file);
    FileHandler fileHandler(&addFile);
    fileHandler.readPatientData(allPatients, waitingPatients);
    addFile.close();

    logCommand("System Admin imported patient data from " + file + "\n");
}

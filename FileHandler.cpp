// Eric Jackman, CSC 402 - Hospital Administration Console App

#include "FileHandler.h"

FileHandler::FileHandler(fstream *file) : file(file) {}

void FileHandler::writePatientData(vector<Patient> *allPatients) {
    if (file->is_open()) {
        vector<Patient>::const_iterator itr;
        for (itr = allPatients->begin(); itr != allPatients->end() - 1; ++itr) {
            *file << itr->toString() << "\n";
        }
        *file << itr->toString();
    } else cout << "Could not save data\n";
}

void FileHandler::readPatientData(vector<Patient> *allPatients,
                                  priority_queue<Patient, vector<Patient>, greater<>> *waitingPatients) {
    if (file->is_open()) {
        string line, fName, mName, lName, suffix, doctor, treated, priority;
        vector<string> ailments;  // holds list of a patient's ailments

        while (getline(*file, line)) {  // loop until the end of the file
            // Read input for one patient
            if ((line.find("firstName")) != string::npos) {
                fName = line.substr(10, line.length() - 10);
            } else if ((line.find("middleName")) != string::npos) {
                mName = line.substr(11, line.length() - 11);
            } else if ((line.find("lastName")) != string::npos) {
                lName = line.substr(9, line.length() - 9);
            } else if ((line.find("suffix")) != string::npos) {
                suffix = line.substr(7, line.length() - 7);
            } else if ((line.find("ailment")) != string::npos) {
                ailments.push_back(line.substr(8, line.length() - 8));
            } else if ((line.find("doctor")) != string::npos) {
                doctor = line.substr(7, line.length() - 7);
            } else if ((line.find("treated")) != string::npos) {
                treated = line.substr(8, line.length() - 8);
            } else if ((line.find("priority")) != string::npos) {
                priority = line.substr(9, line.length() - 9);
            } else if (line.empty()) {  // empty line means that all data has been read for the current patient
                // Creates a patient object and adds it to the vector
                try {
                    allPatients->emplace_back(fName, mName, lName, suffix, doctor, ailments, stoi(treated),
                                              stoi(priority));
                    ailments.clear();  // vector is cleared so the next patient doesn't get the previous patient's ailments
                } catch (exception) { cout << "Error reading file"; }
            }
        }

        // Adds the final patient to the vector
        try {
            allPatients->emplace_back(fName, mName, lName, suffix, doctor, ailments, stoi(treated), stoi(priority));
        } catch (exception) { cout << "Error reading file"; }

        // Add untreated patients to waiting list
        *waitingPatients = priority_queue<Patient, vector<Patient>, greater<>>();  // clear queue to avoid repeats
        vector<Patient>::const_iterator itr;
        for (itr = allPatients->begin(); itr != allPatients->end(); ++itr) {
            if (itr->getTreated() == 0)
                waitingPatients->push(*itr);
        }
    } else cout << "Failed to open file";
}

// Eric Jackman, CSC 402 - Hospital Administration Console App

#include "FileHandler.h"
#include "User.h"

using namespace std;

int main() {
    vector<Patient> allPatients;  // list of all patients
    priority_queue<Patient, vector<Patient>, greater<>> waitingPatients;  // waiting list of untreated patients

    // Input patients from file
    fstream patientsFile("patientData.txt");
    FileHandler fileHandler(&patientsFile);
    fileHandler.readPatientData(&allPatients, &waitingPatients);
    patientsFile.close();

    // Prompt user to select account
    User user(&allPatients, &waitingPatients);
    user.getCommand();

    // Reopen file for output
    fstream patientsOut("patientData.txt");
    FileHandler fileHandler2(&patientsOut);
    fileHandler2.writePatientData(&allPatients);
    patientsOut.close();

    return 0;
}

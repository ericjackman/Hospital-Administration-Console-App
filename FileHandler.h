// Eric Jackman, CSC 402 - Hospital Administration Console App

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Patient.h"

using namespace std;

class FileHandler {
private:
    fstream *file;
public:
    explicit FileHandler(fstream *file);

    void writePatientData(vector<Patient> *allPatients);

    void readPatientData(vector<Patient> *allPatients, priority_queue<Patient, vector<Patient>, greater<>> *waitingPatients);
};

#endif

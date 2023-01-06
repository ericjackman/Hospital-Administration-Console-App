// Eric Jackman, CSC 402 - Hospital Administration Console App

#ifndef USER_H
#define USER_H

#include "Patient.h"
#include "FileHandler.h"
#include <queue>
#include <map>
#include <algorithm>
#include <limits>
#include <thread>
#include <chrono>

using namespace std;

class User {
protected:
    static int debugMode;
    vector<Patient> *allPatients;  // list of all patients in the system
    priority_queue<Patient, vector<Patient>, greater<>> *waitingPatients;  // waiting list
    map<string, string> commands;  // list of commands available
public:
    User(vector<Patient> *allPatients, priority_queue<Patient, vector<Patient>, greater<>> *waitingPatients);

    void outputPatients();

    void help();

    void logCommand(const string &str);

    virtual void getCommand();
};

class Nurse : public User {
public:
    Nurse(vector<Patient> *allPatients, priority_queue<Patient, vector<Patient>, greater<>> *waitingPatients);

    void addPatient();

    void getCommand() override;
};

class Doctor : public User {
public:
    Doctor(vector<Patient> *allPatients, priority_queue<Patient, vector<Patient>, greater<>> *waitingPatients);

    void getNextPatient();

    void treatNextPatient();

    void getReport();

    void printTreated();

    void getCommand() override;
};

class HospAdmin : public User {
public:
    HospAdmin(vector<Patient> *allPatients, priority_queue<Patient, vector<Patient>, greater<>> *waitingPatients);

    void getWaitingPatients();

    void getByDoctor();

    void treatAll();

    void getCommand() override;
};

class SysAdmin : public User {
public:
    SysAdmin(vector<Patient> *allPatients, priority_queue<Patient, vector<Patient>, greater<>> *waitingPatients);

    static void toggleDebugMode();

    void bulkAddPatients();

    void getCommand() override;
};

#endif

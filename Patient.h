// Eric Jackman, CSC 402 - Hospital Administration Console App

#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Patient {
private:
    string firstName;
    string middleName;
    string lastName;
    string fullName;
    string suffix;
    string doctor;
    vector<string> ailments;
    int treated;
    int priority;
public:
    Patient(const string &firstName, const string &middleName, const string &lastName, const string &suffix,
            const string &doctor, const vector<string> &ailments, int treated, int priority);

    const string &getFirstName() const;

    void setFirstName(const string &firstName);

    const string &getMiddleName() const;

    void setMiddleName(const string &middleName);

    const string &getLastName() const;

    void setLastName(const string &lastName);

    const string &getFullName() const;

    void setFullName(const string &fullName);

    const string &getSuffix() const;

    void setSuffix(const string &suffix);

    const string &getDoctor() const;

    void setDoctor(const string &doctor);

    const vector<string> &getAilments() const;

    void setAilments(const vector<string> &ailments);

    int getTreated() const;

    void setTreated(int treated);

    int getPriority() const;

    void setPriority(int priority);

    string toString() const;

    friend bool operator<(const Patient &lhs, const Patient &rhs);

    friend bool operator>(const Patient &lhs, const Patient &rhs);
};

#endif

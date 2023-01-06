// Eric Jackman, CSC 402 - Hospital Administration Console App

#include "Patient.h"

bool operator<(const Patient &lhs, const Patient &rhs) {
    return lhs.getPriority() < rhs.getPriority();
}

bool operator>(const Patient &lhs, const Patient &rhs) {
    return lhs.getPriority() > rhs.getPriority();
}

Patient::Patient(const string &firstName, const string &middleName, const string &lastName, const string &suffix,
                 const string &doctor, const vector<string> &ailments, int treated, int priority)
        : firstName(firstName), middleName(middleName), lastName(lastName), suffix(suffix),
          doctor(doctor), ailments(ailments), treated(treated), priority(priority) {
    Patient::fullName = lastName + ", " + firstName + " " + middleName[0];
}

const string &Patient::getFirstName() const {
    return firstName;
}

void Patient::setFirstName(const string &firstName) {
    Patient::firstName = firstName;
}

const string &Patient::getMiddleName() const {
    return middleName;
}

void Patient::setMiddleName(const string &middleName) {
    Patient::middleName = middleName;
}

const string &Patient::getLastName() const {
    return lastName;
}

void Patient::setLastName(const string &lastName) {
    Patient::lastName = lastName;
}

const string &Patient::getFullName() const {
    return fullName;
}

void Patient::setFullName(const string &fullName) {
    Patient::fullName = fullName;
}

const string &Patient::getSuffix() const {
    return suffix;
}

void Patient::setSuffix(const string &suffix) {
    Patient::suffix = suffix;
}

const string &Patient::getDoctor() const {
    return doctor;
}

void Patient::setDoctor(const string &doctor) {
    Patient::doctor = doctor;
}

const vector<string> &Patient::getAilments() const {
    return ailments;
}

void Patient::setAilments(const vector<string> &ailments) {
    Patient::ailments = ailments;
}

int Patient::getTreated() const {
    return treated;
}

void Patient::setTreated(int treated) {
    Patient::treated = treated;
}

int Patient::getPriority() const {
    return priority;
}

void Patient::setPriority(int priority) {
    Patient::priority = priority;
}

string Patient::toString() const {
    string output;
    output = "firstName:" + firstName + "\n";
    output += "middleName:" + middleName + "\n";
    output += "lastName:" + lastName + "\n";
    output += "suffix:" + suffix + "\n";
    vector<string>::const_iterator itr;
    for (itr = ailments.begin(); itr != ailments.end(); ++itr) {
        output += "ailment:" + *itr + "\n";
    }
    output += "doctor:" + doctor + "\n";
    output += "treated:" + to_string(treated) + "\n";
    output += "priority:" + to_string(priority) + "\n";
    return output;
}

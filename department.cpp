#include "department.h"
#include "nurse.h"
#include "patient.h"
#include "doctor.h"
#include <iostream>

// Constructor
Department::Department(const std::string& name)
    : name(name) {
}

// Copy Constructor
Department::Department(const Department& other)
    : name(other.name), doctors(other.doctors), nurses(other.nurses), patients(other.patients) {
}

// Destructor
Department::~Department() 
{
    // Note: We don't own these pointers, so we don't delete them
    doctors.clear();
    nurses.clear();
    patients.clear();
}

// Getters
const std::string& Department::getName() const { return name;}
std::vector<Doctor*> Department::getDoctors() const{ return doctors;}
std::vector<Nurse*> Department::getNurses() const{ return nurses;}
std::vector<Patient*> Department::getPatients() const { return patients;}
Doctor* Department::getMainDoctor() const { return doctors.empty() ? nullptr : doctors[0];}
Nurse* Department::getMainNurse() const { return nurses.empty() ? nullptr : nurses[0];}

Patient* Department::getPatient() const 
{
    // For backward compatibility, return the first patient
    return patients.empty() ? nullptr : patients[0];
}

// Setters
bool Department::setName(const std::string& newName) 
{
    if (newName.empty()) 
    {
        return false;
    }
    name = newName;
    return true;
}

bool Department::addDoctor(Doctor* newDoctor) 
{
    if (newDoctor == nullptr) {
        return false;
    }
    doctors.push_back(newDoctor);
    return true;
}

bool Department::addNurse(Nurse* newNurse) {
    if (newNurse == nullptr) {
        return false;
    }
    nurses.push_back(newNurse);
    return true;
}

bool Department::addPatient(Patient* newPatient) {
    if (newPatient == nullptr) {
        return false;
    }
    patients.push_back(newPatient);
    return true;
}

// Print Department Details
void Department::printDepartment() const {
    std::cout << "Department: " << name << std::endl;

    // Print doctors
    std::cout << "Doctors: " << doctors.size() << std::endl;
    for (const auto& doctor : doctors) {
        if (doctor != nullptr) {
            std::cout << "  - " << doctor->getName() << std::endl;
        }
    }

    // Print nurses
    std::cout << "Nurses: " << nurses.size() << std::endl;
    for (const auto& nurse : nurses) {
        if (nurse != nullptr) {
            std::cout << "  - " << nurse->getName() << std::endl;
        }
    }

    // Print patients
    std::cout << "Patients: " << patients.size() << std::endl;
    for (const auto& patient : patients) {
        if (patient != nullptr) {
            std::cout << "  - " << patient->getName() << std::endl;
        }
    }
}

// Implementation of += operator for adding a doctor to department
Department& Department::operator+=(Doctor* doc) {
    if (doc != nullptr) {
        addDoctor(doc);
        
        // Also update the doctor's department reference
        doc->setDepartment(this);
    }
    return *this;
}

// Implementation of += operator for adding a nurse to department
Department& Department::operator+=(Nurse* nur) {
    if (nur != nullptr) {
        addNurse(nur);
        
        // Also update the nurse's department reference
        nur->setDepartment(this);
    }
    return *this;
}
#include "visitCard.h"
#include "patient.h"
#include "department.h"
#include "doctor.h"
#include "nurse.h"
#include <iostream>

// Constructor
VisitCard::VisitCard(const std::string& arrivalDate, const std::string& visitGoal, 
                     Patient* patient, Department* department, Doctor* doctor, Nurse* nurse)
    : arrivalDate(arrivalDate), visitGoal(visitGoal), thePatient(patient), 
      theDepartment(department), theDoctor(doctor), theNurse(nurse) {
}

// Copy Constructor
VisitCard::VisitCard(const VisitCard& other)
    : arrivalDate(other.arrivalDate), visitGoal(other.visitGoal), 
      thePatient(other.thePatient), theDepartment(other.theDepartment),
      theDoctor(other.theDoctor), theNurse(other.theNurse) {
}

// Destructor
VisitCard::~VisitCard() {
    // No dynamic memory to deallocate
}

// Getters
const std::string& VisitCard::getArrivalDate() const {
    return arrivalDate;
}

const std::string& VisitCard::getVisitGoal() const {
    return visitGoal;
}

Patient* VisitCard::getPatient() const {
    return thePatient;
}

Department* VisitCard::getDepartment() const {
    return theDepartment;
}

Doctor* VisitCard::getDoctor() const {
    return theDoctor;
}

Nurse* VisitCard::getNurse() const {
    return theNurse;
}

// Setters
bool VisitCard::setArrivalDate(const std::string& newDate) {
    if (newDate.empty()) {
        return false;
    }
    arrivalDate = newDate;
    return true;
}

bool VisitCard::setVisitGoal(const std::string& newGoal) {
    if (newGoal.empty()) {
        return false;
    }
    visitGoal = newGoal;
    return true;
}

bool VisitCard::setPatient(Patient* newPatient) {
    if (newPatient == nullptr) {
        return false;
    }
    thePatient = newPatient;
    return true;
}

bool VisitCard::setDepartment(Department* newDepartment) {
    if (newDepartment == nullptr) {
        return false;
    }
    theDepartment = newDepartment;
    return true;
}

bool VisitCard::setDoctor(Doctor* newDoctor) {
    if (newDoctor == nullptr) {
        return false;
    }
    theDoctor = newDoctor;
    return true;
}

bool VisitCard::setNurse(Nurse* newNurse) {
    if (newNurse == nullptr) {
        return false;
    }
    theNurse = newNurse;
    return true;
}

// Print visit card details
void VisitCard::printVisitCard() const {
    std::cout << "Visit Card Details:" << std::endl;
    std::cout << "Arrival Date: " << arrivalDate << std::endl;
    std::cout << "Visit Goal: " << visitGoal << std::endl;

    if (thePatient != nullptr) {
        std::cout << "Patient: " << thePatient->getName() << std::endl;
    } else {
        std::cout << "Patient: Not assigned" << std::endl;
    }
    
    if (theDepartment != nullptr) {
        std::cout << "Department: " << theDepartment->getName() << std::endl;
    } else {
        std::cout << "Department: Not assigned" << std::endl;
    }

    if (theDoctor != nullptr) {
        std::cout << "Doctor: " << theDoctor->getName() << std::endl;
    } else {
        std::cout << "Doctor: Not assigned" << std::endl;
    }

    if (theNurse != nullptr) {
        std::cout << "Nurse: " << theNurse->getName() << std::endl;
    } else {
        std::cout << "Nurse: Not assigned" << std::endl;
    }
}
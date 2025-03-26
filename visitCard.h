#ifndef __VISIT_CARD__H
#define __VISIT_CARD__H

#include <string>

class Patient;
class Department;
class Doctor;
class Nurse;

class VisitCard {
private:  
    std::string arrivalDate;
    std::string visitGoal;
    Patient* thePatient;
    Department* theDepartment;
    Doctor* theDoctor;
    Nurse* theNurse;

public:
    // Constructor
    VisitCard(const std::string& arrivalDate = "", const std::string& visitGoal = "", 
              Patient* patient = nullptr, Department* department = nullptr, 
              Doctor* doctor = nullptr, Nurse* nurse = nullptr);

    // Copy Constructor
    VisitCard(const VisitCard& other);

    // Destructor
    ~VisitCard();

    // Getters
    const std::string& getArrivalDate() const;
    const std::string& getVisitGoal() const;
    Patient* getPatient() const;
    Department* getDepartment() const;
    Doctor* getDoctor() const;
    Nurse* getNurse() const;

    // Setters (Return bool to indicate success)
    bool setArrivalDate(const std::string& newDate);
    bool setVisitGoal(const std::string& newGoal);
    bool setPatient(Patient* newPatient);
    bool setDepartment(Department* newDepartment);
    bool setDoctor(Doctor* newDoctor);
    bool setNurse(Nurse* newNurse);

    // Print visit card details
    void printVisitCard() const;
};

#endif // __VISIT_CARD__H
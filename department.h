#ifndef __DEPARTMENT_H
#define __DEPARTMENT_H

#include <string>
#include <vector>

class Doctor;    // Forward declaration
class Nurse;     // Forward declaration
class Patient;   // Forward declaration

class Department {
private:
    std::string name;
    std::vector<Doctor*> doctors;
    std::vector<Nurse*> nurses;
    std::vector<Patient*> patients;

public:
    // Constructor
    Department(const std::string& name = "");
    
    // Copy Constructor
    Department(const Department& other);
    
    // Destructor
    ~Department();
    
    // Operator overloading
    Department& operator+=(Doctor* doc);
    Department& operator+=(Nurse* nur);
    
    // Getters
    const std::string& getName() const;
    std::vector<Doctor*> getDoctors() const;
    std::vector<Nurse*> getNurses() const;
    std::vector<Patient*> getPatients() const;
    Doctor* getMainDoctor() const;
    Nurse* getMainNurse() const;
    Patient* getPatient() const; // For backward compatibility
    
    // Setters
    bool setName(const std::string& newName);
    bool addDoctor(Doctor* newDoctor);
    bool addNurse(Nurse* newNurse);
    bool addPatient(Patient* newPatient);
    
    // Print department details
    void printDepartment() const;
};

#endif // __DEPARTMENT_H
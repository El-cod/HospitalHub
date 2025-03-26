#ifndef __NURSE_H
#define __NURSE_H

#include "employee.h"
#include <string>

class Department; // Forward declaration

class Nurse : public Employee {
private:
    int yearsOfExperience;

public:
    // Constructor
    Nurse(const std::string& name = "", int id = 0, int yearsOfExperience = 0, 
          Department* department = nullptr);
    
    // Copy Constructor
    Nurse(const Nurse& other);
    
    // Destructor
    virtual ~Nurse();
    
    // Getters
    int getYearsOfExperience() const;
    
    // Setters
    bool setYearsOfExperience(int newExperience);
    
    // Print nurse details
    virtual void print() const override;
    
    // Operator overloading - for input
    friend std::istream& operator>>(std::istream& is, Nurse& nurse);
};

// Input operator declaration
std::istream& operator>>(std::istream& is, Nurse& nurse);

#endif // __NURSE_H

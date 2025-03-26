#ifndef __DOCTOR_H
#define __DOCTOR_H

#include "employee.h"
#include <string>

class Department; // Forward declaration

class Doctor : public virtual Employee 
{
private:
    std::string expertise;

public:
    // Constructor
    Doctor(const std::string& name = "", int id = 0, const std::string& expertise = "", 
           Department* department = nullptr);
    
    // Copy Constructor
    Doctor(const Doctor& other);
    
    // Destructor
    virtual ~Doctor();
    
    // Getters
    const std::string& getExpertise() const;
    
    // Setters
    bool setExpertise(const std::string& newExpertise);
    
    // Print doctor details
    virtual void print() const override;
    
    // Operator overloading - for input
    friend std::istream& operator>>(std::istream& is, Doctor& doc);
};

// Input operator declaration
std::istream& operator>>(std::istream& is, Doctor& doc);

#endif // __DOCTOR_H

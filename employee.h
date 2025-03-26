#ifndef __EMPLOYEE_H
#define __EMPLOYEE_H

#include "person.h"
#include <string>

class Department; // Forward declaration

class Employee : public Person {
private:
    Department* department;

public:
    // Constructor
    Employee(const std::string& name = "", int id = 0, Department* department = nullptr);
    
    // Copy Constructor
    Employee(const Employee& other);
    
    // Destructor
    virtual ~Employee();
    
    // Getters
    Department* getDepartment() const;
    
    // Setters
    bool setDepartment(Department* newDepartment);
    
    // Print employee details
    virtual void print() const override;
};

#endif // __EMPLOYEE_H

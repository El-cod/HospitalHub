#include "nurse.h"
#include "department.h"
#include <iostream>

// Constructor
Nurse::Nurse(const std::string& name, int id, int yearsOfExperience, Department* department)
    : Employee(name, id, department), yearsOfExperience(yearsOfExperience) {}

// Copy Constructor
Nurse::Nurse(const Nurse& other)
    : Employee(other), yearsOfExperience(other.yearsOfExperience) {}

// Destructor
Nurse::~Nurse() 
{
    // No dynamic memory to deallocate
}

// Getters
int Nurse::getYearsOfExperience() const 
{
    return yearsOfExperience;
}

// Setters
bool Nurse::setYearsOfExperience(int newExperience) 
{
    if (newExperience < 0) {
        return false;
    }
    yearsOfExperience = newExperience;
    return true;
}

// Print nurse details
void Nurse::print() const 
{
    std::cout << "Nurse Information:" << std::endl;
    Employee::print();
    std::cout << "Years of Experience: " << yearsOfExperience << std::endl;
}

// Implementation of input operator for Nurse
std::istream& operator>>(std::istream& is, Nurse& nurse) 
{
    std::string name;
    int id, yearsOfExperience;
    
    std::cout << "Enter nurse name: ";
    std::getline(is, name);
    
    std::cout << "Enter nurse ID: ";
    is >> id;
    
    std::cout << "Enter years of experience: ";
    is >> yearsOfExperience;
    is.ignore(); // Clear the newline character
    
    nurse.setName(name);
    nurse.setId(id);
    nurse.setYearsOfExperience(yearsOfExperience);
    
    return is;
}

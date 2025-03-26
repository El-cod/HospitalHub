#include "doctor.h"
#include "department.h"
#include <iostream>

// Constructor
Doctor::Doctor(const std::string& name, int id, const std::string& expertise, Department* department)
    : Employee(name, id, department), expertise(expertise) {
}

// Copy Constructor
Doctor::Doctor(const Doctor& other)
    : Employee(other), expertise(other.expertise) {
}

// Destructor
Doctor::~Doctor() {
    // No dynamic memory to deallocate
}

// Getters
const std::string& Doctor::getExpertise() const {
    return expertise;
}

// Setters
bool Doctor::setExpertise(const std::string& newExpertise) 
{
    if (newExpertise.empty()) 
    {
        return false;
    }
    expertise = newExpertise;
    return true;
}

// Print doctor details
void Doctor::print() const 
{
    std::cout << "Doctor Information:" << std::endl;
    Employee::print();
    std::cout << "Expertise: " << expertise << std::endl;
}

// Implementation of input operator for Doctor
std::istream& operator>>(std::istream& is, Doctor& doc) 
{
    std::string name, expertise;
    int id;
    
    std::cout << "Enter doctor name: ";
    std::getline(is, name);
    
    std::cout << "Enter doctor ID: ";
    is >> id;
    is.ignore(); // Clear the newline character
    
    std::cout << "Enter doctor expertise: ";
    std::getline(is, expertise);
    
    doc.setName(name);
    doc.setId(id);
    doc.setExpertise(expertise);
    
    return is;
}
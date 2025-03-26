#include "employee.h"
#include "department.h"
#include <iostream>

// Constructor
Employee::Employee(const std::string& name, int id, Department* department)
    : Person(name, id), department(department) {}

// Copy Constructor
Employee::Employee(const Employee& other)
    : Person(other), department(other.department) {}

// Destructor
Employee::~Employee() 
{
    // Note: department is not owned by Employee, so we don't delete it
}

// Getters
Department* Employee::getDepartment() const 
{
    return department;
}

// Setters
bool Employee::setDepartment(Department* newDepartment) 
{
    department = newDepartment;
    return true;
}

// Print employee details
void Employee::print() const 
{
    Person::print();
    
    if (department != nullptr) 
    {
        std::cout << "Assigned to Department: " << department->getName() << std::endl;
    } else {
        std::cout << "Not assigned to any department" << std::endl;
    }
}

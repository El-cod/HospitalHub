#include "patient.h"
#include "visitCard.h"
#include <iostream>

// Constructor
Patient::Patient(const std::string& name, int id, int birthYear, const std::string& sex)
    : Person(name, id), birthYear(birthYear), sex(sex), visitCard(nullptr) {}

// Copy Constructor
Patient::Patient(const Patient& other)
    : Person(other), birthYear(other.birthYear), sex(other.sex), visitCard(other.visitCard) {}

// Destructor
Patient::~Patient() 
{
    // Note: visitCard is not owned by Patient, so we don't delete it
}

// Getters
int Patient::getBirthYear() const 
{
    return birthYear;
}

const std::string& Patient::getSex() const 
{
    return sex;
}

VisitCard* Patient::getVisitCard() const 
{
    return visitCard;
}

// Setters
bool Patient::setBirthYear(int newBirthYear) 
{
    if (newBirthYear < 0) 
    {
        return false;
    }
    birthYear = newBirthYear;
    return true;
}

bool Patient::setSex(const std::string& newSex) 
{
    if (newSex.empty()) 
    {
        return false;
    }
    sex = newSex;
    return true;
}

bool Patient::setVisitCard(VisitCard* newVisitCard) 
{
    if (newVisitCard == nullptr) 
    {
        return false;
    }
    visitCard = newVisitCard;
    return true;
}

// Print patient details
void Patient::print() const 
{
    std::cout << "Patient Information:" << std::endl;
    Person::print();
    std::cout << "Birth Year: " << birthYear << ", Sex: " << sex << std::endl;
}

// Implementation of input operator for Patient
std::istream& operator>>(std::istream& is, Patient& patient) 
{
    std::string name, sex;
    int id, birthYear;
    
    std::cout << "Enter patient name: ";
    std::getline(is, name);
    
    std::cout << "Enter patient ID: ";
    is >> id;
    
    std::cout << "Enter birth year: ";
    is >> birthYear;
    is.ignore(); // Clear the newline character
    
    std::cout << "Enter sex: ";
    std::getline(is, sex);
    
    patient.setName(name);
    patient.setId(id);
    patient.setBirthYear(birthYear);
    patient.setSex(sex);
    
    return is;
}
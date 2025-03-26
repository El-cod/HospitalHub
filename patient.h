#ifndef __PATIENT_H
#define __PATIENT_H

#include "person.h"
#include <string>

class VisitCard; // Forward declaration

class Patient : public Person 
{
private:
    int birthYear;
    std::string sex;
    VisitCard* visitCard;

public:
    // Constructor
    Patient(const std::string& name = "", int id = 0, int birthYear = 2000, 
            const std::string& sex = "");
    
    // Copy Constructor
    Patient(const Patient& other);
    
    // Destructor
    virtual ~Patient();
    
    // Getters
    int getBirthYear() const;
    const std::string& getSex() const;
    VisitCard* getVisitCard() const;
    
    // Setters
    bool setBirthYear(int newBirthYear);
    bool setSex(const std::string& newSex);
    bool setVisitCard(VisitCard* newVisitCard);
    
    // Print patient details
    virtual void print() const override;
    
    // Operator overloading - for input
    friend std::istream& operator>>(std::istream& is, Patient& patient);
};

// Input operator declaration
std::istream& operator>>(std::istream& is, Patient& patient);

#endif // __PATIENT_H

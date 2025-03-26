#ifndef __PERSON_H
#define __PERSON_H

#include <string>

class Person 
{
private:
    std::string name;
    int id;

public:
    // Constructor
    Person(const std::string& name = "", int id = 0);
    
    // Copy Constructor
    Person(const Person& other);
    
    // Destructor
    virtual ~Person();
    
    // Getters
    const std::string& getName() const;
    int getId() const;
    
    // Setters
    bool setName(const std::string& newName);
    bool setId(int newId);
    
    // Print person details
    virtual void print() const;
};

#endif // __PERSON_H

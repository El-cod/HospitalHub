#include "person.h"
#include <iostream>

// Constructor
Person::Person(const std::string& name, int id) 
    : name(name), id(id) {
}

// Copy Constructor
Person::Person(const Person& other) 
    : name(other.name), id(other.id) {
}

// Destructor
Person::~Person() {
    // No dynamic memory to deallocate
}

// Getters
const std::string& Person::getName() const { 
    return name; 
}

int Person::getId() const { 
    return id; 
}

// Setters
bool Person::setName(const std::string& newName) {
    if (newName.empty()) {
        return false;
    }
    name = newName;
    return true;
}

bool Person::setId(int newId) {
    if (newId < 0) {
        return false;
    }
    id = newId;
    return true;
}

// Print person details
void Person::print() const {
    std::cout << "Name: " << name << ", ID: " << id << std::endl;
}

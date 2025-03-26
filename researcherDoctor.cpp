#include "researcherDoctor.h"
#include "department.h"
#include <iostream>

// Constructor
ResearcherDoctor::ResearcherDoctor(const std::string& name, int id, 
    const std::string& expertise, Department* department)
: Employee(name, id, department),  // Initialize shared base class ONCE
Researcher(name, id),
Doctor(name, id, expertise, department) {
}


// Copy Constructor
ResearcherDoctor::ResearcherDoctor(const ResearcherDoctor& other)
    : Researcher(other), Doctor(other) {
}

// Destructor
ResearcherDoctor::~ResearcherDoctor() {
    // Any ResearcherDoctor-specific cleanup would go here
}

// Resolve method ambiguities
const std::string& ResearcherDoctor::getResearcherName() const {
    // Use Researcher's implementation
    return Researcher::getName();
}

int ResearcherDoctor::getResearcherId() const {
    // Use Researcher's implementation
    return Researcher::getId();
}

// Print researcher doctor details
void ResearcherDoctor::print() const {
    std::cout << "Researcher-Doctor Information:" << std::endl;
    // We'll use the Researcher's print method as a base
    Researcher::print();
    std::cout << "Medical Expertise: " << Doctor::getExpertise() << std::endl;
}

void ResearcherDoctor::printResearcherDoctor() const {
    std::cout << "===== Researcher-Doctor Information =====" << std::endl;
    std::cout << "Name: " << getResearcherName() << ", ID: " << getResearcherId() << std::endl;
    std::cout << "Medical Expertise: " << Doctor::getExpertise() << std::endl;
    
    // Print department information if assigned
    Department* dept = Doctor::getDepartment();
    if (dept != nullptr) {
        std::cout << "Assigned to Department: " << dept->getName() << std::endl;
    } else {
        std::cout << "Not assigned to any department" << std::endl;
    }
    
    // Print researcher information
    std::cout << "Number of Published Articles: " << Researcher::getNumArticles() << std::endl;
    
    // Print all articles if any exist
    if (Researcher::getNumArticles() > 0) {
        std::cout << "\nPublished Articles:" << std::endl;
        Researcher::printResearcherInfo();
    }
    
    std::cout << "=====================================" << std::endl;
}
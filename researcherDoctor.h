#ifndef __RESEARCHER_DOCTOR_H
#define __RESEARCHER_DOCTOR_H

#include "researcher.h"
#include "doctor.h"
#include <string>

class Department; // Forward declaration

class ResearcherDoctor : public Researcher, public Doctor {
public:
    // Constructor
    ResearcherDoctor(const std::string& name = "", int id = 0, 
                     const std::string& expertise = "", Department* department = nullptr);
    
    // Copy Constructor
    ResearcherDoctor(const ResearcherDoctor& other);
    
    // Destructor
    virtual ~ResearcherDoctor();
    
    // Resolve method ambiguities
    const std::string& getResearcherName() const;
    int getResearcherId() const;
    
    // Print researcher doctor details
    virtual void print() const override;
    void printResearcherDoctor() const;
};

#endif // __RESEARCHER_DOCTOR_H
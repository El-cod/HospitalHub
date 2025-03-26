#ifndef HOSPITAL_MANAGER_H
#define HOSPITAL_MANAGER_H

#include "hospital.h"

class HospitalManager {
private:
    Hospital hospital;
    
    // Menu options
    enum MenuOption {
        ADD_DEPARTMENT = 1,
        ADD_NURSE,
        ADD_DOCTOR,
        ADD_VISITOR,
        ADD_RESEARCHER,
        ADD_ARTICLE_TO_RESEARCHER,
        SHOW_DEPARTMENT_PATIENTS,
        SHOW_ALL_STAFF,
        SHOW_ALL_RESEARCHERS,
        SEARCH_PATIENT_BY_ID,
        TEST_ADD_DOCTOR_OPERATOR,
        TEST_ADD_NURSE_OPERATOR,
        TEST_INPUT_OPERATOR,
        TEST_ADD_STAFF_TO_DEPARTMENT_OPERATOR,
        TEST_COMPARE_RESEARCHERS_OPERATOR,
        EXIT
    };
    
    // Menu methods
    void displayMenu() const;
    void processUserChoice(int choice);
    
    // Sample data initialization
    void initializeSampleData();

public:
    // Constructor
    HospitalManager(const std::string& hospitalName = "General Hospital");
    
    // Run the hospital management system
    void run();
};

#endif // HOSPITAL_MANAGER_H
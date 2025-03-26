
//___________Student name: Eldad Rabinovitch
#include "hospitalManager.h"
#include <iostream>

int main() {
    std::cout << "Starting Hospital Management System" << std::endl;
    
    // Create and run the hospital manager
    HospitalManager manager("Asaf Medical Center");
    manager.run();
    
    return 0;
}

// Compilation command for Unix systems:
//clang++ -o project_part3 main.cpp department.cpp doctor.cpp nurse.cpp patient.cpp article.cpp researcher.cpp research_center.cpp hospital.cpp hospitalManager.cpp visitCard.cpp researcherDoctor.cpp employee.cpp person.cpp
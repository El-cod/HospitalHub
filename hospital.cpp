#include "hospital.h"
#include "employee.h"
#include "doctor.h"
#include "nurse.h"
#include "department.h"
#include "patient.h"
#include "visitCard.h"
#include "researcher.h"
#include "researcherDoctor.h"
#include "article.h"
#include "research_center.h"
#include <iostream>
#include <algorithm>
#include <limits>

// Constructor
Hospital::Hospital(const std::string& name)
    : name(name), researchCenter(std::make_unique<ResearchCenter>("Deep Medical Research")) {
    std::cout << "Creating Hospital\n" << std::endl;
}

// Destructor
Hospital::~Hospital() {
    // Clean up dynamically allocated memory
    for (auto* employee : employees) {
        delete employee;
    }
    
    for (auto* department : departments) {
        delete department;
    }
    
    for (auto* visitCard : visitCards) {
        delete visitCard;
    }
    
    for (auto* patient : patients) {
        delete patient;
    }
    
    // ResearchCenter is automatically deleted by unique_ptr
}

// Operator overloading
Hospital& Hospital::operator+=(Doctor& doctor) {
    addDoctorToHospital(doctor);
    std::cout << "Doctor " << doctor.getName() << " added to hospital with += operator." << std::endl;
    return *this;
}

Hospital& Hospital::operator+=(Nurse& nurse) {
    addNurseToHospital(nurse);
    std::cout << "Nurse " << nurse.getName() << " added to hospital with += operator." << std::endl;
    return *this;
}

// Department management
bool Hospital::departmentExists(const Department& department) const {
    for (const auto* existingDepartment : departments) {
        if (existingDepartment->getName() == department.getName()) {
            return true;
        }
    }
    return false;
}

int Hospital::findDepartmentIndex(const Department& department) const {
    for (size_t i = 0; i < departments.size(); i++) {
        if (departments[i]->getName() == department.getName()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

Department* Hospital::findDepartmentByName(const std::string& departmentName) const {
    for (auto* department : departments) {
        if (department->getName() == departmentName) {
            return department;
        }
    }
    return nullptr;
}

bool Hospital::addDepartmentToHospital(Department& department) {
    if (departmentExists(department)) {
        std::cout << "The department " << department.getName() 
                  << " was NOT added because it already exists" << std::endl;
        return false;
    }
    
    departments.push_back(new Department(department));
    std::cout << "The department " << department.getName() 
              << " was added to AllDepartments array successfully" << std::endl;
    return true;
}

void Hospital::addDepartmentInteractive() {
    std::string departmentName;
    
    std::cout << "Enter department name: ";
    std::getline(std::cin, departmentName);
    
    // Validate input
    if (departmentName.empty()) {
        std::cout << "Department name cannot be empty. Operation canceled." << std::endl;
        return;
    }
    
    // Check if department already exists
    for (const auto* department : departments) {
        if (department->getName() == departmentName) {
            std::cout << "A department with this name already exists. Operation canceled." << std::endl;
            return;
        }
    }
    
    // Create new department
    Department* newDepartment = new Department(departmentName);
    
    // Add department to hospital
    departments.push_back(newDepartment);
    std::cout << "Department '" << departmentName << "' added successfully." << std::endl;
}

// Nurse management
bool Hospital::nurseExists(const Nurse& nurse) const {
    for (const auto* employee : employees) {
        // Check if employee is a Nurse and has the same ID
        const Nurse* nursePtr = dynamic_cast<const Nurse*>(employee);
        if (nursePtr && nursePtr->getId() == nurse.getId()) {
            return true;
        }
    }
    return false;
}

bool Hospital::addNurseToHospital(Nurse& nurse) {
    if (nurseExists(nurse)) {
        return false;
    }
    
    employees.push_back(new Nurse(nurse));
    std::cout << "The nurse " << nurse.getName() << " was added to hospital successfully" << std::endl;
    return true;
}

int Hospital::findNurseIndex(const Nurse& nurse) const {
    for (size_t i = 0; i < employees.size(); i++) {
        // Check if employee is a Nurse and has the same name
        const Nurse* nursePtr = dynamic_cast<const Nurse*>(employees[i]);
        if (nursePtr && nursePtr->getName() == nurse.getName()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool Hospital::addNurseToDepartmentInHospital(Nurse& nurse, Department& department) {
    bool nurseAdded = false;
    bool departmentAdded = false;
    
    // Check if nurse exists, add if not
    if (!nurseExists(nurse)) {
        addNurseToHospital(nurse);
        nurseAdded = true;
    }
    
    // Check if department exists, add if not
    if (!departmentExists(department)) {
        addDepartmentToHospital(department);
        departmentAdded = true;
    }
    
    // Find the department and nurse in the hospital arrays
    int departmentIndex = findDepartmentIndex(department);
    if (departmentIndex == -1) {
        return false;
    }
    
    // Find the nurse in the employees vector
    Nurse* nursePtr = nullptr;
    for (auto* employee : employees) {
        Nurse* candidateNurse = dynamic_cast<Nurse*>(employee);
        if (candidateNurse && candidateNurse->getName() == nurse.getName()) {
            nursePtr = candidateNurse;
            break;
        }
    }
    
    if (nursePtr == nullptr) {
        return false;
    }
    
    // Add nurse to department and update nurse's department
    departments[departmentIndex]->addNurse(nursePtr);
    nursePtr->setDepartment(departments[departmentIndex]);
    
    // Print appropriate messages
    if (!nurseAdded) {
        std::cout << "The nurse " << nurse.getName() 
                  << " did NOT add to hospital because they already exist" << std::endl;
    }
    
    if (!departmentAdded) {
        std::cout << "The department " << department.getName() 
                  << " was already in the hospital" << std::endl;
    }
    
    std::cout << "The nurse " << nurse.getName() 
              << " was successfully assigned to department: " << department.getName() << std::endl;
    
    return true;
}

Nurse* Hospital::getNurseByName(const std::string& nurseName) {
    for (auto* employee : employees) {
        Nurse* nurse = dynamic_cast<Nurse*>(employee);
        if (nurse && nurse->getName() == nurseName) {
            return nurse;
        }
    }
    return nullptr;
}

void Hospital::addNurseInteractive() {
    std::string nurseName;
    int nurseId, yearsExperience;
    
    // Collect nurse information
    std::cout << "Enter nurse name: ";
    std::getline(std::cin, nurseName);
    
    // Validate name
    if (nurseName.empty()) {
        std::cout << "Nurse name cannot be empty. Operation canceled." << std::endl;
        return;
    }
    
    // Get nurse ID
    std::cout << "Enter nurse ID: ";
    std::cin >> nurseId;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid ID format. Operation canceled." << std::endl;
        return;
    }
    
    // Check if nurse with this ID already exists
    for (auto* employee : employees) {
        Nurse* nurse = dynamic_cast<Nurse*>(employee);
        if (nurse && nurse->getId() == nurseId) {
            std::cout << "A nurse with this ID already exists. Operation canceled." << std::endl;
            return;
        }
    }
    
    // Get years of experience
    std::cout << "Enter years of experience: ";
    std::cin >> yearsExperience;
    
    if (std::cin.fail() || yearsExperience < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid years of experience. Operation canceled." << std::endl;
        return;
    }
    
    // Display available departments
    if (departments.empty()) {
        std::cout << "No departments available. Please add a department first." << std::endl;
        return;
    }
    
    std::cout << "\nAvailable departments:" << std::endl;
    for (size_t i = 0; i < departments.size(); i++) {
        std::cout << i+1 << ". " << departments[i]->getName() << std::endl;
    }
    
    // Get department selection
    std::cout << "Select department number for the nurse: ";
    int deptChoice;
    std::cin >> deptChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (std::cin.fail() || deptChoice < 1 || deptChoice > static_cast<int>(departments.size())) {
        std::cin.clear();
        std::cout << "Invalid department selection. Operation canceled." << std::endl;
        return;
    }
    
    Department* selectedDept = departments[deptChoice-1];
    
    // Create new nurse with selected department
    Nurse* newNurse = new Nurse(nurseName, nurseId, yearsExperience, selectedDept);
    
    // Add nurse to hospital and department
    employees.push_back(newNurse);
    selectedDept->addNurse(newNurse);
    
    std::cout << "Nurse '" << nurseName << "' added successfully and assigned to department '" 
              << selectedDept->getName() << "'." << std::endl;
}

// Doctor management
bool Hospital::doctorExists(const Doctor& doctor) const {
    for (const auto* employee : employees) {
        // Check if employee is a Doctor and has the same ID
        const Doctor* doctorPtr = dynamic_cast<const Doctor*>(employee);
        if (doctorPtr && doctorPtr->getId() == doctor.getId()) {
            return true;
        }
    }
    return false;
}

bool Hospital::addDoctorToHospital(Doctor& doctor) {
    if (doctorExists(doctor)) {
        return false;
    }
    
    employees.push_back(new Doctor(doctor));
    std::cout << "The doctor " << doctor.getName() << " was added to hospital successfully" << std::endl;
    return true;
}

int Hospital::findDoctorIndex(const Doctor& doctor) const {
    for (size_t i = 0; i < employees.size(); i++) {
        // Check if employee is a Doctor and has the same name
        const Doctor* doctorPtr = dynamic_cast<const Doctor*>(employees[i]);
        if (doctorPtr && doctorPtr->getName() == doctor.getName()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool Hospital::addDoctorToDepartmentInHospital(Doctor& doctor, Department& department) {
    bool doctorAdded = false;
    bool departmentAdded = false;
    
    // Check if doctor exists, add if not
    if (!doctorExists(doctor)) {
        addDoctorToHospital(doctor);
        doctorAdded = true;
    }
    
    // Check if department exists, add if not
    if (!departmentExists(department)) {
        addDepartmentToHospital(department);
        departmentAdded = true;
    }
    
    // Find the department and doctor in the hospital arrays
    int departmentIndex = findDepartmentIndex(department);
    if (departmentIndex == -1) {
        return false;
    }
    
    // Find the doctor in the employees vector
    Doctor* doctorPtr = nullptr;
    for (auto* employee : employees) {
        Doctor* candidateDoctor = dynamic_cast<Doctor*>(employee);
        if (candidateDoctor && candidateDoctor->getName() == doctor.getName()) {
            doctorPtr = candidateDoctor;
            break;
        }
    }
    
    if (doctorPtr == nullptr) {
        return false;
    }
    
    // Add doctor to department and update doctor's department
    departments[departmentIndex]->addDoctor(doctorPtr);
    doctorPtr->setDepartment(departments[departmentIndex]);
    
    // Print appropriate messages
    if (!doctorAdded) {
        std::cout << "The doctor " << doctor.getName() 
                  << " did NOT add to hospital because they already exist" << std::endl;
    }
    
    if (!departmentAdded) {
        std::cout << "The department " << department.getName() 
                  << " was already in the hospital" << std::endl;
    }
    
    std::cout << "The doctor " << doctor.getName() 
              << " was successfully assigned to department: " << department.getName() << std::endl;
    
    return true;
}

Doctor* Hospital::getDoctorByName(const std::string& doctorName) {
    for (auto* employee : employees) {
        Doctor* doctor = dynamic_cast<Doctor*>(employee);
        if (doctor && doctor->getName() == doctorName) {
            return doctor;
        }
    }
    return nullptr;
}

void Hospital::addDoctorInteractive() {
    std::string doctorName, expertise;
    int doctorId;
    
    // Collect doctor information
    std::cout << "Enter doctor name: ";
    std::getline(std::cin, doctorName);
    
    // Validate name
    if (doctorName.empty()) {
        std::cout << "Doctor name cannot be empty. Operation canceled." << std::endl;
        return;
    }
    
    // Get doctor ID
    std::cout << "Enter doctor ID: ";
    std::cin >> doctorId;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid ID format. Operation canceled." << std::endl;
        return;
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Check if doctor with this ID already exists
    for (auto* employee : employees) {
        Doctor* doctor = dynamic_cast<Doctor*>(employee);
        if (doctor && doctor->getId() == doctorId) {
            std::cout << "A doctor with this ID already exists. Operation canceled." << std::endl;
            return;
        }
    }
    
    // Get expertise
    std::cout << "Enter doctor's expertise: ";
    std::getline(std::cin, expertise);
    
    if (expertise.empty()) {
        std::cout << "Expertise cannot be empty. Operation canceled." << std::endl;
        return;
    }
    
    // Display available departments
    if (departments.empty()) {
        std::cout << "No departments available. Please add a department first." << std::endl;
        return;
    }
    
    std::cout << "\nAvailable departments:" << std::endl;
    for (size_t i = 0; i < departments.size(); i++) {
        std::cout << i+1 << ". " << departments[i]->getName() << std::endl;
    }
    
    // Get department selection
    std::cout << "Select department number for the doctor: ";
    int deptChoice;
    std::cin >> deptChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (std::cin.fail() || deptChoice < 1 || deptChoice > static_cast<int>(departments.size())) {
        std::cin.clear();
        std::cout << "Invalid department selection. Operation canceled." << std::endl;
        return;
    }
    
    Department* selectedDept = departments[deptChoice-1];
    
    // Create new doctor with selected department
    Doctor* newDoctor = new Doctor(doctorName, doctorId, expertise, selectedDept);
    
    // Add doctor to hospital and department
    employees.push_back(newDoctor);
    selectedDept->addDoctor(newDoctor);
    
    std::cout << "Doctor '" << doctorName << "' added successfully and assigned to department '" 
              << selectedDept->getName() << "'." << std::endl;
}

// VisitCard management
Patient* Hospital::getPatientInVisitCardIfExists(const Patient& patient) const {
    for (const auto* visitCard : visitCards) {
        if (visitCard->getPatient() && visitCard->getPatient()->getId() == patient.getId()) {
            return visitCard->getPatient();
        }
    }
    return nullptr;
}

bool Hospital::visitCardExists(const VisitCard& visitCard) const {
    // Handle the case where patient is nullptr
    if (visitCard.getPatient() == nullptr) {
        for (const auto* existingVisitCard : visitCards) {
            // Compare other properties to determine equality
            if (existingVisitCard->getArrivalDate() == visitCard.getArrivalDate() &&
                existingVisitCard->getVisitGoal() == visitCard.getVisitGoal()) {
                return true;
            }
        }
        return false;
    }
    
    // Normal case with patient pointer
    for (const auto* existingVisitCard : visitCards) {
        if (existingVisitCard->getPatient() != nullptr &&
            existingVisitCard->getPatient()->getId() == visitCard.getPatient()->getId()) {
            return true;
        }
    }
    return false;
}

bool Hospital::addVisitCardToHospital(VisitCard& visitCard) {
    if (visitCardExists(visitCard)) {
        return false;
    }
    
    visitCards.push_back(new VisitCard(visitCard));
    return true;
}

// Patient management
bool Hospital::patientExists(const Patient& patient) const {
    for (const auto* existingPatient : patients) {
        if (existingPatient->getId() == patient.getId()) {
            return true;
        }
    }
    return false;
}

bool Hospital::addPatientToHospital(Patient& patient) {
    if (patientExists(patient)) {
        return false;
    }
    
    patients.push_back(new Patient(patient));
    return true;
}

VisitCard* Hospital::createNewVisitCardAndReturn(const std::string& newDate, const std::string& newGoal, 
                                               Department* department, Doctor* doctor, Nurse* nurse) {
    if (newDate.empty() || newGoal.empty() || department == nullptr) {
        std::cout << "Error: Missing required fields for VisitCard." << std::endl;
        return nullptr;
    }

    VisitCard* newVisitCard = new VisitCard(newDate, newGoal, nullptr, department, doctor, nurse);
    visitCards.push_back(newVisitCard);

    std::cout << "VisitCard created successfully!" << std::endl;
    return newVisitCard;
}

Patient* Hospital::getPatientById(int id) {
    for (auto* patient : patients) {
        if (patient->getId() == id) {
            return patient;
        }
    }
    return nullptr;
}

bool Hospital::addVisitCardToPatient(Patient& patient, VisitCard& visitCard) {
    // First, ensure the patient is in the hospital system
    if (!patientExists(patient)) {
        if (!addPatientToHospital(patient)) {
            std::cout << "Failed to add patient to hospital." << std::endl;
            return false;
        }
    }
    
    // Set up the bidirectional relationship safely
    // First link the patient to the visit card
    if (visitCard.getPatient() == nullptr) {
        if (!visitCard.setPatient(&patient)) {
            std::cout << "Failed to set patient in visit card." << std::endl;
            return false;
        }
    }
    
    // Then link the visit card to the patient
    if (!patient.setVisitCard(&visitCard)) {
        std::cout << "Failed to set visit card for patient." << std::endl;
        return false;
    }
    
    // Add the visit card to hospital's records if not already there
    if (!visitCardExists(visitCard)) {
        if (!addVisitCardToHospital(visitCard)) {
            std::cout << "Failed to add visit card to hospital records." << std::endl;
            return false;
        }
    }
    
    // Update department with the patient if available
    Department* dept = visitCard.getDepartment();
    if (dept != nullptr) {
        dept->addPatient(&patient);
    }
    
    return true;
}

Patient* Hospital::createNewPatient(const std::string& patientName, int patientId, 
                                  int patientBirth, const std::string& patientSex) {
    // Validate parameters
    if (patientName.empty() || patientSex.empty() || patientId <= 0 || patientBirth <= 0) {
        std::cout << "Error: Invalid patient details!" << std::endl;
        return nullptr;
    }

    // Create new Patient object
    Patient* newPatient = new Patient(patientName, patientId, patientBirth, patientSex);
    
    // Add patient to hospital
    if (!addPatientToHospital(*newPatient)) {
        std::cout << "Error: Could not add patient to hospital!" << std::endl;
        delete newPatient;  // Free memory in case of failure
        return nullptr;
    }

    std::cout << "New patient added successfully!" << std::endl;
    return newPatient;
}

void Hospital::searchPatientByID() {
    int patientId;
    std::cout << "Enter patient ID to search: ";
    std::cin >> patientId;
    
    // Validate input
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a numeric ID." << std::endl;
        return;
    }
    
    // Search for the patient
    Patient* foundPatient = getPatientById(patientId);
    
    if (!foundPatient) {
        std::cout << "No patient found with ID: " << patientId << std::endl;
        return;
    }
    
    // Display patient name
    std::cout << "Patient Name: " << foundPatient->getName() << std::endl;
    
    // Try to find their department
    Department* patientDept = nullptr;
    
    // First check if they have a visit card
    VisitCard* visitCard = foundPatient->getVisitCard();
    if (visitCard && visitCard->getDepartment()) {
        patientDept = visitCard->getDepartment();
        std::cout << "Department: " << patientDept->getName() << std::endl;
        return;
    }
    
    // If no department found through visit card, search through all departments
    for (auto* department : departments) {
        auto deptPatients = department->getPatients();
        for (auto* deptPatient : deptPatients) {
            if (deptPatient && deptPatient->getId() == patientId) {
                std::cout << "Department: " << department->getName() << std::endl;
                return;
            }
        }
    }
    
    // If we reach here, no department was found
    std::cout << "Patient is not currently assigned to any department." << std::endl;
}

// Researcher management
bool Hospital::addResearcher(const Researcher& researcher) {
    researchCenter->addResearcher(researcher);
    return true;
}

void Hospital::showAllResearchers() const {
    researchCenter->displayResearchers();
}

bool Hospital::addResearcherDoctor(const ResearcherDoctor& researcherDoctor) {
    // Add as a doctor to the hospital
    if (!doctorExists(researcherDoctor)) {
        employees.push_back(new ResearcherDoctor(researcherDoctor));
    }
    
    // Add as a researcher to the research center
    return researchCenter->addResearcherDoctor(researcherDoctor);
}

void Hospital::addResearcherInteractive() {
    std::string name;
    int id;
    bool isDoctor;
    
    std::cout << "Enter researcher name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter researcher ID: ";
    std::cin >> id;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid ID. Operation canceled." << std::endl;
        return;
    }
    
    std::cout << "Is this researcher also a doctor? (1 for yes, 0 for no): ";
    std::cin >> isDoctor;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Operation canceled." << std::endl;
        return;
    }
    
    if (isDoctor) {
        std::string expertise;
        Department* department = nullptr;
        
        std::cout << "Enter doctor expertise: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, expertise);
        
        std::cout << "Assign to a department? (1 for yes, 0 for no): ";
        bool assignDepartment;
        std::cin >> assignDepartment;
        
        if (assignDepartment) {
            // Display available departments
            std::cout << "Available departments:" << std::endl;
            for (size_t i = 0; i < departments.size(); i++) {
                std::cout << i+1 << ". " << departments[i]->getName() << std::endl;
            }
            
            std::cout << "Choose department number (0 to skip): ";
            int deptChoice;
            std::cin >> deptChoice;
            
            if (deptChoice > 0 && deptChoice <= static_cast<int>(departments.size())) {
                department = departments[deptChoice-1];
            }
        }
        
        // Create and add ResearcherDoctor
        ResearcherDoctor* resDoc = new ResearcherDoctor(name, id, expertise, department);
        employees.push_back(resDoc);
        researchCenter->addResearcherDoctor(*resDoc);
        
        std::cout << "Researcher-Doctor " << name << " added successfully." << std::endl;
    } else {
        // Create and add regular Researcher
        Researcher researcher(name, id);
        addResearcher(researcher);
        
        std::cout << "Researcher " << name << " added successfully." << std::endl;
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Article management
bool Hospital::addArticleToResearcher(const Article& article, const Researcher& researcher) {
    return researchCenter->addArticleToResearcher(article, researcher);
}

// Display functions
void Hospital::showAllStaff() const {
    if (employees.empty()) {
        std::cout << "No staff members found. Please add staff and try again." << std::endl;
        return;
    }
    
    std::cout << "Hospital Staff:" << std::endl;
    std::cout << "Total Staff Members: " << employees.size() << std::endl;
    
    // Print doctors
    std::cout << "\nDoctors:" << std::endl;
    for (const auto* employee : employees) {
        const Doctor* doctor = dynamic_cast<const Doctor*>(employee);
        if (doctor) {
            doctor->print();
            std::cout << "---------------------------" << std::endl;
        }
    }
    
    // Print nurses
    std::cout << "\nNurses:" << std::endl;
    for (const auto* employee : employees) {
        const Nurse* nurse = dynamic_cast<const Nurse*>(employee);
        if (nurse && !dynamic_cast<const Doctor*>(nurse)) { // Ensure not a ResearcherDoctor
            nurse->print();
            std::cout << "---------------------------" << std::endl;
        }
    }
}

void Hospital::showAllDepartmentPatients() const {
    if (departments.empty()) {
        std::cout << "No departments available in the hospital." << std::endl;
        return;
    }
    
    // Display available departments
    std::cout << "\nAvailable departments:" << std::endl;
    for (size_t i = 0; i < departments.size(); i++) {
        std::cout << i+1 << ". " << departments[i]->getName() << std::endl;
    }
    
    // Get user choice
    int choice;
    std::cout << "\nEnter department number: ";
    std::cin >> choice;
    
    if (std::cin.fail() || choice < 1 || choice > static_cast<int>(departments.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid department selection." << std::endl;
        return;
    }
    
    Department* selectedDept = departments[choice-1];
    std::cout << "\nPatients in department '" << selectedDept->getName() << "':" << std::endl;
    
    // Get all patients in the selected department
    auto departmentPatients = selectedDept->getPatients();
    
    if (departmentPatients.empty()) {
        std::cout << "No patients found in this department." << std::endl;
        return;
    }
    
    // Display all patients
    for (const auto* patient : departmentPatients) {
        patient->print();
        std::cout << "---------------------------" << std::endl;
    }
}

void Hospital::printHospitalName() const {
    std::cout << "The Hospital's name is " << name << std::endl;
}
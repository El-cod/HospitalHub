#include "hospitalManager.h"
#include "department.h"
#include "doctor.h"
#include "nurse.h"
#include "patient.h"
#include "visitCard.h"
#include "researcher.h"
#include "researcherDoctor.h"
#include "article.h"
#include <iostream>
#include <limits>

// Constructor
HospitalManager::HospitalManager(const std::string& hospitalName)
    : hospital(hospitalName) {
    initializeSampleData();
}

// Sample data initialization
void HospitalManager::initializeSampleData() 
{
    // Create departments
    Department* heartDept = new Department("Heart");
    Department* surgeryDept = new Department("Surgery");
    Department* oncologyDept = new Department("Oncology");
    Department* neurologyDept = new Department("Neurology");
    
    // Add departments to hospital
    hospital.addDepartmentToHospital(*heartDept);
    hospital.addDepartmentToHospital(*surgeryDept);
    hospital.addDepartmentToHospital(*oncologyDept);
    hospital.addDepartmentToHospital(*neurologyDept);
    
    // Create doctors
    Doctor* doc1 = new Doctor("John Smith", 101, "Cardiology", heartDept);
    Doctor* doc2 = new Doctor("Sarah Johnson", 102, "General Surgery", surgeryDept);
    
    // Add doctors to hospital
    hospital.addDoctorToHospital(*doc1);
    hospital.addDoctorToHospital(*doc2);
    
    // Create nurses
    Nurse* nurse1 = new Nurse("Mary Wilson", 201, 5, heartDept);
    Nurse* nurse2 = new Nurse("Robert Brown", 202, 7, surgeryDept);
    
    // Add nurses to hospital
    hospital.addNurseToHospital(*nurse1);
    hospital.addNurseToHospital(*nurse2);
    
    // Create patients
    Patient* patient1 = new Patient("David Lee", 301, 1980, "Male");
    Patient* patient2 = new Patient("Linda Chen", 302, 1975, "Female");
    
    // Add patients to hospital
    hospital.addPatientToHospital(*patient1);
    hospital.addPatientToHospital(*patient2);
    
    // Create visit cards
    VisitCard* visit1 = new VisitCard("2025-03-10", "Chest pain", patient1, heartDept, doc1, nurse1);
    VisitCard* visit2 = new VisitCard("2025-03-09", "Fractured arm", patient2, surgeryDept, doc2, nurse2);
    
    // Add visit cards to hospital and link to patients
    hospital.addVisitCardToHospital(*visit1);
    hospital.addVisitCardToHospital(*visit2);
    patient1->setVisitCard(visit1);
    patient2->setVisitCard(visit2);
    
    // Add patients to departments
    heartDept->addPatient(patient1);
    surgeryDept->addPatient(patient2);
    
    // Create researchers and articles
    Researcher* researcher1 = new Researcher("Michael Taylor", 401);
    ResearcherDoctor* researcherDoctor1 = new ResearcherDoctor("Jennifer Adams", 402, "Oncology", oncologyDept);
    
    Article* article1 = new Article("Medical Journal of Cardiology", "Advances in Heart Surgery Techniques", "2024-12-15");
    Article* article2 = new Article("Oncology Research", "New Cancer Treatment Approaches", "2025-01-20");
    
    // Add researchers and articles
    hospital.addResearcher(*researcher1);
    hospital.addResearcherDoctor(*researcherDoctor1);
    hospital.addArticleToResearcher(*article1, *researcher1);
    hospital.addArticleToResearcher(*article2, *researcherDoctor1);
}

// Display menu
void HospitalManager::displayMenu() const {
    std::cout << "\n====== Hospital Management System ======\n";
    std::cout << "1. Add Department\n";
    std::cout << "2. Add Nurse\n";
    std::cout << "3. Add Doctor\n";
    std::cout << "4. Add Visitor\n";
    std::cout << "5. Add Researcher\n";
    std::cout << "6. Add Article to Researcher\n";
    std::cout << "7. Show All Department Patients\n";
    std::cout << "8. Show All Staff\n";
    std::cout << "9. Show All Researchers\n";
    std::cout << "10. Search Patient by ID\n";
    std::cout << "11. Test Add Doctor to Hospital Operator (+=)\n";
    std::cout << "12. Test Add Nurse to Hospital Operator (+=)\n";
    std::cout << "13. Test Input Operator (>>)\n";
    std::cout << "14. Test Add Staff to Department Operator (+=)\n";
    std::cout << "15. Test Compare Researchers Operator (<)\n";
    std::cout << "16. Exit\n";
    std::cout << "Choose option: ";
}

// Process user choice
void HospitalManager::processUserChoice(int choice) 
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch (static_cast<MenuOption>(choice)) {
        case ADD_DEPARTMENT:
            hospital.addDepartmentInteractive();
            break;
            
        case ADD_NURSE:
            hospital.addNurseInteractive();
            break;
            
        case ADD_DOCTOR:
            hospital.addDoctorInteractive();
            break;
            
        case ADD_VISITOR: {
            char visitChoice;
            std::cout << "Has the patient visited before? (y/n): ";
            std::cin >> visitChoice;
            
            while (visitChoice != 'y' && visitChoice != 'Y' && visitChoice != 'n' && visitChoice != 'N') {
                std::cout << "Invalid choice. Enter 'y' or 'n': ";
                std::cin >> visitChoice;
            }
            
            Patient* patient = nullptr;
            // Get or create patient
            if (visitChoice == 'y' || visitChoice == 'Y') {
                int patientId;
                std::cout << "Enter patient ID: ";
                std::cin >> patientId;
                
                // Find existing patient
                patient = hospital.getPatientById(patientId);
                if (!patient) {
                    std::cout << "Patient with ID " << patientId << " not found. Please try again." << std::endl;
                    break;
                }
                std::cout << "Found patient: " << patient->getName() << std::endl;
            } else {
                // Create new patient
                std::string patientName, patientSex;
                int patientId, patientBirth;
                
                std::cout << "Enter patient name: ";
                std::cin.ignore();
                std::getline(std::cin, patientName);
                
                std::cout << "Enter patient ID: ";
                std::cin >> patientId;
                
                std::cout << "Enter patient birth year: ";
                std::cin >> patientBirth;
                
                std::cout << "Enter patient sex: ";
                std::cin.ignore();
                std::getline(std::cin, patientSex);
                
                // Create and add new patient
                patient = hospital.createNewPatient(patientName, patientId, patientBirth, patientSex);
                if (!patient) {
                    std::cout << "Failed to create new patient. Please try again." << std::endl;
                    break;
                }
            }
            
            // Get visit details
            std::string arrivalDate, visitGoal, departmentName;
            
            std::cout << "Enter arrival date (YYYY-MM-DD): ";
            std::cin.ignore(std::cin.gcount());
            std::getline(std::cin, arrivalDate);
            
            std::cout << "Enter visit goal: ";
            std::getline(std::cin, visitGoal);
            
            std::cout << "Enter department name: ";
            std::getline(std::cin, departmentName);
            
            Department* department = hospital.findDepartmentByName(departmentName);
            if (!department) {
                std::cout << "Department '" << departmentName << "' not found. Visit cannot be created." << std::endl;
                break;
            }
            
            // Get treating staff
            Doctor* doctor = nullptr;
            Nurse* nurse = nullptr;
            
            char staffType;
            std::cout << "Who is the primary caregiver? (d for doctor / n for nurse): ";
            std::cin >> staffType;
            
            if (staffType == 'd' || staffType == 'D') {
                std::string doctorName;
                std::cout << "Enter doctor name: ";
                std::cin.ignore();
                std::getline(std::cin, doctorName);
                
                doctor = hospital.getDoctorByName(doctorName);
                if (!doctor) {
                    std::cout << "Doctor '" << doctorName << "' not found. Using none." << std::endl;
                }
            } else if (staffType == 'n' || staffType == 'N') {
                std::string nurseName;
                std::cout << "Enter nurse name: ";
                std::cin.ignore();
                std::getline(std::cin, nurseName);
                
                nurse = hospital.getNurseByName(nurseName);
                if (!nurse) {
                    std::cout << "Nurse '" << nurseName << "' not found. Using none." << std::endl;
                }
            } else {
                std::cout << "Invalid caregiver type. No caregiver will be assigned." << std::endl;
            }
            
            // Create visit card
            VisitCard* visitCard = hospital.createNewVisitCardAndReturn(arrivalDate, visitGoal, department, doctor, nurse);
            if (!visitCard) {
                std::cout << "Failed to create visit card." << std::endl;
                break;
            }
            
            // Associate visit card with patient
            if (hospital.addVisitCardToPatient(*patient, *visitCard)) {
                std::cout << "Visit successfully created for patient " << patient->getName() << "." << std::endl;
            } else {
                std::cout << "Failed to associate visit card with patient." << std::endl;
            }
            break;
        }
            
        case ADD_RESEARCHER:
            hospital.addResearcherInteractive();
            break;
            
        case ADD_ARTICLE_TO_RESEARCHER: {
            // Implementation for adding article to researcher
            std::string researcherName;
            std::cout << "Enter researcher name: ";
            std::getline(std::cin, researcherName);
            
            // For simplicity, we'll create a new article
            std::string journalName, title, publicationDate;
            
            std::cout << "Enter journal name: ";
            std::getline(std::cin, journalName);
            
            std::cout << "Enter article title: ";
            std::getline(std::cin, title);
            
            std::cout << "Enter publication date (YYYY-MM-DD): ";
            std::getline(std::cin, publicationDate);
            
            Article article(journalName, title, publicationDate);
            Researcher researcher(researcherName, 0); // ID doesn't matter for search
            
            if (hospital.addArticleToResearcher(article, researcher)) {
                std::cout << "Article added successfully to researcher: " << researcherName << std::endl;
            } else {
                std::cout << "Failed to add article. Researcher may not exist." << std::endl;
            }
            break;
        }
            
        case SHOW_DEPARTMENT_PATIENTS:
            hospital.showAllDepartmentPatients();
            break;
            
        case SHOW_ALL_STAFF:
            hospital.showAllStaff();
            break;
            
        case SHOW_ALL_RESEARCHERS:
            hospital.showAllResearchers();
            break;
            
        case SEARCH_PATIENT_BY_ID:
            hospital.searchPatientByID();
            break;
            
        case TEST_ADD_DOCTOR_OPERATOR: {
            std::string doctorName, expertise;
            int doctorId;
            
            std::cout << "Enter doctor name for += operator test: ";
            std::getline(std::cin, doctorName);
            
            std::cout << "Enter doctor ID: ";
            std::cin >> doctorId;
            std::cin.ignore();
            
            std::cout << "Enter expertise: ";
            std::getline(std::cin, expertise);
            
            Doctor doctor(doctorName, doctorId, expertise);
            
            // Add the doctor using the += operator
            hospital += doctor;
            
            std::cout << "Doctor added using += operator." << std::endl;
            break;
        }
            
        case TEST_ADD_NURSE_OPERATOR: {
            std::string nurseName;
            int nurseId, yearsExp;
            
            std::cout << "Enter nurse name for += operator test: ";
            std::getline(std::cin, nurseName);
            
            std::cout << "Enter nurse ID: ";
            std::cin >> nurseId;
            
            std::cout << "Enter years of experience: ";
            std::cin >> yearsExp;
            std::cin.ignore();
            
            Nurse nurse(nurseName, nurseId, yearsExp);
            
            // Add the nurse using the += operator
            hospital += nurse;
            
            std::cout << "Nurse added using += operator." << std::endl;
            break;
        }
            
        case TEST_INPUT_OPERATOR: {
            std::cout << "Testing input operator for Doctor:" << std::endl;
            Doctor newDoc("temp", 0, "temp");
            std::cin >> newDoc;
            std::cout << "Doctor details after input:" << std::endl;
            newDoc.print();
            
            std::cout << "\nTesting input operator for Nurse:" << std::endl;
            Nurse newNurse("temp", 0, 0);
            std::cin >> newNurse;
            std::cout << "Nurse details after input:" << std::endl;
            newNurse.print();
            
            std::cout << "\nTesting input operator for Patient:" << std::endl;
            Patient newPatient;
            std::cin >> newPatient;
            std::cout << "Patient details after input:" << std::endl;
            newPatient.print();
            break;
        }
            
        case TEST_ADD_STAFF_TO_DEPARTMENT_OPERATOR: {
            std::string deptName;
            std::cout << "Enter department name: ";
            std::getline(std::cin, deptName);
            
            Department* selectedDept = hospital.findDepartmentByName(deptName);
            if (!selectedDept) {
                std::cout << "Department not found." << std::endl;
                break;
            }
            
            std::cout << "1. Add Doctor\n2. Add Nurse\nChoice: ";
            int staffChoice;
            std::cin >> staffChoice;
            std::cin.ignore();
            
            if (staffChoice == 1) {
                std::string docName, expertise;
                int docId;
                
                std::cout << "Enter doctor name: ";
                std::getline(std::cin, docName);
                
                std::cout << "Enter doctor ID: ";
                std::cin >> docId;
                std::cin.ignore();
                
                std::cout << "Enter expertise: ";
                std::getline(std::cin, expertise);
                
                Doctor* newDoc = new Doctor(docName, docId, expertise);
                
                // First add the doctor to the hospital, then to the department
                hospital.addDoctorToHospital(*newDoc);
                *selectedDept += newDoc;
                
                std::cout << "Doctor added to hospital and department using += operator." << std::endl;
            } else if (staffChoice == 2) {
                std::string nurseName;
                int nurseId, yearsExp;
                
                std::cout << "Enter nurse name: ";
                std::getline(std::cin, nurseName);
                
                std::cout << "Enter nurse ID: ";
                std::cin >> nurseId;
                
                std::cout << "Enter years of experience: ";
                std::cin >> yearsExp;
                std::cin.ignore();
                
                Nurse* newNurse = new Nurse(nurseName, nurseId, yearsExp);
                
                // First add the nurse to the hospital, then to the department
                hospital.addNurseToHospital(*newNurse);
                *selectedDept += newNurse;
                
                std::cout << "Nurse added to hospital and department using += operator." << std::endl;
            } else {
                std::cout << "Invalid staff type selection." << std::endl;
            }
            break;
        }
            
        case TEST_COMPARE_RESEARCHERS_OPERATOR: {
            // Create two researchers
            std::string name1, name2;
            int id1, id2, numArticles1, numArticles2;
            
            std::cout << "Creating two researchers to compare:" << std::endl;
            
            std::cout << "Enter name for Researcher 1: ";
            std::getline(std::cin, name1);
            
            std::cout << "Enter ID for Researcher 1: ";
            std::cin >> id1;
            
            std::cout << "Enter number of articles to add for Researcher 1: ";
            std::cin >> numArticles1;
            std::cin.ignore();
            
            Researcher res1(name1, id1);
            
            // Add articles to researcher 1
            for (int i = 0; i < numArticles1; i++) {
                std::string journalName, title, date;
                
                std::cout << "Enter journal name for article " << i+1 << ": ";
                std::getline(std::cin, journalName);
                
                std::cout << "Enter title for article " << i+1 << ": ";
                std::getline(std::cin, title);
                
                std::cout << "Enter publication date for article " << i+1 << " (YYYY-MM-DD): ";
                std::getline(std::cin, date);
                
                Article art(journalName, title, date);
                res1.addArticle(art);
            }
            
            std::cout << "\nEnter name for Researcher 2: ";
            std::getline(std::cin, name2);
            
            std::cout << "Enter ID for Researcher 2: ";
            std::cin >> id2;
            
            std::cout << "Enter number of articles to add for Researcher 2: ";
            std::cin >> numArticles2;
            std::cin.ignore();
            
            Researcher res2(name2, id2);
            
            // Add articles to researcher 2
            for (int i = 0; i < numArticles2; i++) {
                std::string journalName, title, date;
                
                std::cout << "Enter journal name for article " << i+1 << ": ";
                std::getline(std::cin, journalName);
                
                std::cout << "Enter title for article " << i+1 << ": ";
                std::getline(std::cin, title);
                
                std::cout << "Enter publication date for article " << i+1 << " (YYYY-MM-DD): ";
                std::getline(std::cin, date);
                
                Article art(journalName, title, date);
                res2.addArticle(art);
            }
            
            std::cout << "\nResearcher 1 (" << name1 << ") has " << res1.getNumArticles() << " articles." << std::endl;
            std::cout << "Researcher 2 (" << name2 << ") has " << res2.getNumArticles() << " articles." << std::endl;
            
            if (res1 < res2) {
                std::cout << "Researcher 1 has fewer articles than Researcher 2." << std::endl;
            } else {
                std::cout << "Researcher 1 does not have fewer articles than Researcher 2." << std::endl;
            }
            break;
        }
            
        case EXIT:
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            break;
            
        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
    }
}

// Run the hospital management system
void HospitalManager::run() 
{
    bool running = true;
    int choice;
    
    while (running) {
        displayMenu();
        std::cin >> choice;
        
        if (std::cin.fail() || choice < 1 || choice > EXIT) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and " << EXIT << "." << std::endl;
            continue;
        }
        
        if (choice == EXIT) {
            running = false;
        } else {
            processUserChoice(choice);
        }
    }
}
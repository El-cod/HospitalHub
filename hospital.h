#ifndef __HOSPITAL_H
#define __HOSPITAL_H

#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Employee;
class Doctor;
class Nurse;
class Department;
class Patient;
class VisitCard;
class Researcher;
class ResearcherDoctor;
class Article;
class ResearchCenter;

class Hospital 
{
private:
    std::string name;
    std::vector<Employee*> employees;           // All employees (doctors, nurses, etc.)
    std::vector<Department*> departments;
    std::vector<VisitCard*> visitCards;
    std::vector<Patient*> patients;
    std::unique_ptr<ResearchCenter> researchCenter;

    // Prevent copy
    Hospital(const Hospital& other) = delete;
    Hospital& operator=(const Hospital& other) = delete;

public:
    // Constructor
    Hospital(const std::string& name = "Hospital");

    // Destructor
    ~Hospital();
    
    // Operator overloading
    Hospital& operator+=(Doctor& doctor);
    Hospital& operator+=(Nurse& nurse);

    // Department management
    bool departmentExists(const Department& department) const;
    int findDepartmentIndex(const Department& department) const;
    Department* findDepartmentByName(const std::string& departmentName) const;
    bool addDepartmentToHospital(Department& department);
    void addDepartmentInteractive();
    
    // Nurse management
    bool nurseExists(const Nurse& nurse) const;
    bool addNurseToHospital(Nurse& nurse);
    int findNurseIndex(const Nurse& nurse) const;
    bool addNurseToDepartmentInHospital(Nurse& nurse, Department& department);
    Nurse* getNurseByName(const std::string& nurseName);
    void addNurseInteractive();
    
    // Doctor management
    bool doctorExists(const Doctor& doctor) const;
    bool addDoctorToHospital(Doctor& doctor);
    int findDoctorIndex(const Doctor& doctor) const;
    bool addDoctorToDepartmentInHospital(Doctor& doctor, Department& department);
    Doctor* getDoctorByName(const std::string& doctorName);
    void addDoctorInteractive();
    
    // VisitCard management
    Patient* getPatientInVisitCardIfExists(const Patient& patient) const;
    bool visitCardExists(const VisitCard& visitCard) const;
    bool addVisitCardToHospital(VisitCard& visitCard);
    
    // Patient management
    bool patientExists(const Patient& patient) const;
    bool addPatientToHospital(Patient& patient);
    VisitCard* createNewVisitCardAndReturn(const std::string& newDate, const std::string& newGoal, 
                                          Department* department, Doctor* doctor, Nurse* nurse);
    Patient* getPatientById(int id);
    bool addVisitCardToPatient(Patient& patient, VisitCard& visitCard);
    Patient* createNewPatient(const std::string& patientName, int patientId, 
                             int patientBirth, const std::string& patientSex);
    void searchPatientByID();
    
    // Researcher management
    bool addResearcher(const Researcher& researcher);
    void showAllResearchers() const;
    bool addResearcherDoctor(const ResearcherDoctor& researcherDoctor);
    void addResearcherInteractive();
    
    // Article management
    bool addArticleToResearcher(const Article& article, const Researcher& researcher);
    
    // Display functions
    void showAllStaff() const;
    void showAllDepartmentPatients() const;
    void printHospitalName() const;
};

#endif // __HOSPITAL_H
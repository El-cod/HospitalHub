# HospitalHub - Hospital Management System

## Overview
The Hospital Management System is a C++ project that implements a comprehensive solution for managing hospital resources. The system is designed using an object-oriented approach and demonstrates advanced features of the language such as inheritance, polymorphism, operator overloading, and templates.

## System Capabilities
* Management of hospital departments
* Registration and administration of medical staff (doctors and nurses)
* Patient tracking and visit management
* Research institute and researcher management
* Documentation and tracking of scientific articles
* Management of doctor-researchers (dual roles)
* Patient search by identification number
* Generation of system reports

## System Architecture
The system consists of several main components:

### Data Model
* `Person` - Base class for all individuals in the system
* `Patient` - Hospital patients
* `Employee` - Base class for hospital staff
* `Doctor` - Medical doctors
* `Nurse` - Nursing staff
* `Department` - Hospital departments
* `VisitCard` - Patient visit records
* `Researcher` - Research institute staff
* `ResearcherDoctor` - Doctors who also serve as researchers
* `Article` - Scientific publications

### Management Module
* `Hospital` - Overall management of the hospital and its resources
* `ResearchCenter` - Management of the research institute and research staff
* `HospitalManager` - User interface and overall system management

## How to Run the System
1. Compile the project with the command:
   ```
   clang++ -o project_part3 main.cpp department.cpp doctor.cpp nurse.cpp patient.cpp article.cpp researcher.cpp research_center.cpp hospital.cpp hospitalManager.cpp visitCard.cpp researcherDoctor.cpp employee.cpp person.cpp
   ```
2. Run the generated binary file:
   ```
   ./project_part3
   ```

## User Interface
The system presents an interactive menu allowing:
1. Add department
2. Add nurse
3. Add doctor
4. Add patient and visit
5. Add researcher
6. Add article to researcher
7. Display patients by department
8. Display all medical staff
9. Display all researchers
10. Search patient by ID
11. Various testing options (operator overloading)
12. Various testing options (operator overloading)
13. Various testing options (operator overloading)
14. Various testing options (operator overloading)
15. Various testing options (operator overloading)

## Technical Features
* Implementation of multiple inheritance (especially in the ResearcherDoctor class)
* Virtual inheritance to handle the diamond inheritance problem
* Use of STL containers (vectors, unordered_maps)
* Operator overloading (+=, >>, <)
* Dynamic memory management and duplicate handling
* Adherence to object-oriented programming principles

## Implementation Notes
* The system carefully manages containment relationships between different objects
* Each class is responsible for cleaning up the resources it allocates
* The system prevents duplications and provides functionality for entity lookup
* Clear separation between business logic and user interface

---
*Developed by Eldad Rabinovitch*

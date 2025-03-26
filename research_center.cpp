#include "research_center.h"
#include "researcher.h"
#include "researcherDoctor.h"
#include "article.h"
#include <iostream>
#include <algorithm>

// Constructor
ResearchCenter::ResearchCenter(const std::string& name)
    : name(name) {
}

// Destructor
ResearchCenter::~ResearchCenter() {
    // Only delete researchers that are owned by the research center
    for (auto* researcher : researchers) {
        if (researcherOwnership[researcher]) {
            delete researcher;
        }
    }
    researchers.clear();
    researcherOwnership.clear();
}

// Getters
const std::string& ResearchCenter::getName() const {
    return name;
}

int ResearchCenter::getNumResearchers() const {
    return static_cast<int>(researchers.size());
}

// Setters
bool ResearchCenter::setName(const std::string& newName) {
    if (newName.empty()) {
        return false;
    }
    name = newName;
    return true;
}

// Researcher management
bool ResearchCenter::researcherExists(const Researcher& researcher) const {
    for (const auto* existingResearcher : researchers) {
        if (existingResearcher->getName() == researcher.getName()) {
            return true;
        }
    }
    return false;
}

bool ResearchCenter::addResearcher(const Researcher& researcher) {
    if (researcherExists(researcher)) {
        std::cout << "The researcher " << researcher.getName() 
                  << " was NOT added because they already exist" << std::endl;
        return false;
    }
    
    // Create a new researcher and mark it as owned by the research center
    Researcher* newResearcher = new Researcher(researcher);
    researchers.push_back(newResearcher);
    researcherOwnership[newResearcher] = true;
    
    std::cout << "The researcher " << researcher.getName() 
              << " was added to researchers array successfully" << std::endl;
    return true;
}

bool ResearchCenter::addResearcherDoctor(const ResearcherDoctor& resDoc) {
    if (researcherExists(resDoc)) {
        std::cout << "Researcher-Doctor " << resDoc.getResearcherName() 
                  << " already exists." << std::endl;
        return false;
    }
    
    // Since ResearcherDoctor is managed by the hospital, we don't own it
    researchers.push_back(const_cast<ResearcherDoctor*>(&resDoc));
    researcherOwnership[const_cast<ResearcherDoctor*>(&resDoc)] = false;
    
    std::cout << "Researcher-Doctor " << resDoc.getResearcherName() 
              << " added successfully." << std::endl;
    return true;
}

bool ResearchCenter::addArticleToResearcher(const Article& article, const Researcher& researcher) {
    int index = findResearcherIndex(researcher);
    if (index != -1) {
        researchers[index]->addArticle(article);
        std::cout << "The researcher " << researcher.getName() 
                  << " added the article: " << article.getTitle() << std::endl;
        return true;
    }
    return false;
}

int ResearchCenter::findResearcherIndex(const Researcher& researcher) const {
    for (size_t i = 0; i < researchers.size(); i++) {
        if (researchers[i]->getName() == researcher.getName()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Display all researchers
void ResearchCenter::displayResearchers() const {
    std::cout << "Research Institute: " << name 
              << ", Number of Researchers: " << researchers.size() << std::endl;
    
    for (const auto* researcher : researchers) {
        researcher->printResearcherInfo();
        std::cout << "---------------------------" << std::endl;
    }
}
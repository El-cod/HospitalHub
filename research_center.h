#ifndef __RESEARCH_CENTER__H
#define __RESEARCH_CENTER__H

#include <string>
#include <vector>
#include <unordered_map>

class Researcher;
class ResearcherDoctor;
class Article;

class ResearchCenter {
private:
    std::string name;
    std::vector<Researcher*> researchers;
    
    // Flag to track which researchers are owned by the research center
    // If the researcher is owned by research center (not by hospital), value is true
    std::unordered_map<Researcher*, bool> researcherOwnership;
    
    // Prevent copy
    ResearchCenter(const ResearchCenter& other) = delete;
    ResearchCenter& operator=(const ResearchCenter& other) = delete;

public:
    // Constructor
    ResearchCenter(const std::string& name = "");
    
    // Destructor
    ~ResearchCenter();
    
    // Getters
    const std::string& getName() const;
    int getNumResearchers() const;
    
    // Setters
    bool setName(const std::string& newName);
    
    // Researcher management
    bool researcherExists(const Researcher& researcher) const;
    bool addResearcher(const Researcher& researcher);
    bool addResearcherDoctor(const ResearcherDoctor& resDoc);
    bool addArticleToResearcher(const Article& article, const Researcher& researcher);
    int findResearcherIndex(const Researcher& researcher) const;
    
    // Display all researchers
    void displayResearchers() const;
};

#endif // __RESEARCH_CENTER__H
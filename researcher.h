#ifndef __RESEARCHER_H
#define __RESEARCHER_H

#include "employee.h"
#include <string>
#include <vector>

class Article; // Forward declaration

class Researcher : virtual public Employee {
private:
    std::vector<Article*> articles;

public:
    // Constructor
    Researcher(const std::string& name = "", int id = 0);
    
    // Copy Constructor
    Researcher(const Researcher& other);
    
    // Destructor
    virtual ~Researcher();
    
    // Getters
    int getNumArticles() const;
    
    // Article management
    bool articleExists(const Article& article) const;
    bool addArticle(const Article& article);
    
    // Print researcher details
    virtual void print() const override;
    virtual void printResearcherInfo() const;
    
    // Operator overloading
    bool operator<(const Researcher& other) const;
};

#endif // __RESEARCHER_H

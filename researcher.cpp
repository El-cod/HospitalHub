#include "researcher.h"
#include "article.h"
#include <iostream>
#include <algorithm>

// Constructor
Researcher::Researcher(const std::string& name, int id)
    : Employee(name, id) {
}

// Copy Constructor
Researcher::Researcher(const Researcher& other)
    : Employee(other) {
    // Deep copy of articles
    for (const auto& article : other.articles) {
        articles.push_back(new Article(*article));
    }
}

// Destructor
Researcher::~Researcher() 
{
    // Clean up article pointers
    for (auto article : articles) 
    {
        delete article;
    }
    articles.clear();
}

// Getters
int Researcher::getNumArticles() const 
{
    return static_cast<int>(articles.size());
}

// Article management
bool Researcher::articleExists(const Article& article) const 
{
    for (const auto& existingArticle : articles) {
        if (existingArticle->getTitle() == article.getTitle()) 
        {
            return true;
        }
    }
    return false;
}

bool Researcher::addArticle(const Article& article) 
{
    if (articleExists(article)) 
    {
        std::cout << "The article '" << article.getTitle() 
                  << "' was NOT added because it already exists." << std::endl;
        return false;
    }
    
    articles.push_back(new Article(article));
    std::cout << "The article '" << article.getTitle() 
              << "' was added successfully." << std::endl;
    return true;
}

// Print researcher details
void Researcher::print() const 
{
    std::cout << "Researcher Information:" << std::endl;
    Employee::print();
    std::cout << "Number of Articles: " << getNumArticles() << std::endl;
}

void Researcher::printResearcherInfo() const 
{
    print();
    
    // Print each article
    if (!articles.empty()) {
        std::cout << "\nPublished Articles:" << std::endl;
        for (const auto& article : articles) 
        {
            article->printArticle();
            std::cout << "---------------------------" << std::endl;
        }
    }
}

// Operator overloading
bool Researcher::operator<(const Researcher& other) const 
{
    return getNumArticles() < other.getNumArticles();
}
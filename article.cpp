#include "article.h"
#include <iostream>

// Constructor
Article::Article(const std::string& journalName, const std::string& title, 
                const std::string& publicationDate)
    : journalName(journalName), title(title), publicationDate(publicationDate) {}

// Copy Constructor
Article::Article(const Article& other)
    : journalName(other.journalName), title(other.title), publicationDate(other.publicationDate) {}

// Destructor
Article::~Article() 
{
    // No dynamic memory to deallocate
}

// Getters
const std::string& Article::getJournalName() const 
{
    return journalName;
}

const std::string& Article::getTitle() const 
{
    return title;
}

const std::string& Article::getPublicationDate() const 
{
    return publicationDate;
}

// Setters
bool Article::setJournalName(const std::string& newJournal) 
{
    if (newJournal.empty()) 
    {
        return false;
    }
    journalName = newJournal;
    return true;
}

bool Article::setTitle(const std::string& newTitle) 
{
    if (newTitle.empty()) 
    {
        return false;
    }
    title = newTitle;
    return true;
}

bool Article::setPublicationDate(const std::string& newDate) 
{
    if (newDate.empty()) 
    {
        return false;
    }
    publicationDate = newDate;
    return true;
}

// Print article details
void Article::printArticle() const 
{
    std::cout << "Title: " << title << ", Journal: " << journalName
              << ", Publication Date: " << publicationDate << std::endl;
}
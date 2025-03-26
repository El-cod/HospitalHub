#ifndef __ARTICLE_H
#define __ARTICLE_H

#include <string>

class Article {
private:
    std::string journalName;
    std::string title;
    std::string publicationDate;

public:
    // Constructor
    Article(const std::string& journalName = "", const std::string& title = "", 
           const std::string& publicationDate = "");
    
    // Copy Constructor
    Article(const Article& other);
    
    // Destructor
    ~Article();
    
    // Getters
    const std::string& getJournalName() const;
    const std::string& getTitle() const;
    const std::string& getPublicationDate() const;
    
    // Setters
    bool setJournalName(const std::string& newJournal);
    bool setTitle(const std::string& newTitle);
    bool setPublicationDate(const std::string& newDate);
    
    // Print article details
    void printArticle() const;
};

#endif // __ARTICLE_H
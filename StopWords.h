//
// Created by cekef on 18-Jan-18.
//
#include <string>
#include <set>

#ifndef PROJECT_STOPWORDS_H
#define PROJECT_STOPWORDS_H


class StopWords {
public:
    //setup the mapping
    StopWords();

    bool operator[](std::string toCheck){
        return stopWords.find(toCheck) == stopWords.end();
    }

private:
    std::set<std::string> stopWords;
};


#endif //PROJECT_STOPWORDS_H

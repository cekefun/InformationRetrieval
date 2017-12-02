//
// Created by cedric on 11/28/17.
//
#include <vector>
#include <string>
extern "C" {
#include "stemmer/api.h"
}
#ifndef PROJECT_STEMMER_H
#define PROJECT_STEMMER_H


class Stemmer {
public:
    /***
     * Constructor for Stemmer
     */
    Stemmer();
    /***
     * Destructor for Stemmer
     */
    ~Stemmer();
    /***
     * Stem a vector of english words
     * @input The vector containing words to stem
     * @return The stemmed vector
     */
    std::vector<std::string> stem(const std::vector<std::string>&);
private:
    SN_env * enviroment;
};


#endif //PROJECT_STEMMER_H

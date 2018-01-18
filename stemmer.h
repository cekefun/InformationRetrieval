//
// Created by cedric on 11/28/17.
//
#include <vector>
#include <string>

#include "stemming/stemming_oleander/english_stem.h"

#ifndef PROJECT_STEMMER_H
#define PROJECT_STEMMER_H


class Stemmer {
public:
    /***
     * Stem a vector of english words
     * @input The vector containing words to stem
     * @return The stemmed vector
     */
    std::vector<std::string> stem(const std::vector<std::string>&);
private:
    stemming::english_stem<> StemEnglish;
};


#endif //PROJECT_STEMMER_H

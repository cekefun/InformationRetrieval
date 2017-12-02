//
// Created by cedric on 11/28/17.
//
#include <iostream>
#include "stemmer.h"
extern "C" {
#include "stemmer/english.h"
}

Stemmer::Stemmer() {
    enviroment = E_create_env();
}

Stemmer::~Stemmer() {
    E_close_env(enviroment);
}

std::vector<std::string> Stemmer::stem(const std::vector<std::string> &v) {
    std::vector<std::string> result;
    for(std::string str : v){
        symbol* temp;
        copy(str.begin(),str.end(), temp);
        SN_set_current(enviroment,str.size(),temp);
        E_stem(enviroment);
        std::string stemmed="";
        for (int j = 0; j < enviroment->l; j++){
            stemmed.push_back(enviroment->p[j]);
        }
        result.push_back(stemmed);
    }
    // For some reason, if I remove this, I get a segfault on the return.
    for (auto i: result){
    }
    return result;
}

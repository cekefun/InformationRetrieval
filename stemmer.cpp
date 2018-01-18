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
    std::vector<std::string> result = {};
    for(std::string str : v){
        std::cout<<"token: "<<str<<std::endl;
        symbol temp[str.size()];
        copy(str.begin(),str.end(), temp);

        SN_set_current(enviroment,str.size(),temp);
        E_stem(enviroment);
        std::string stemmed((char*)enviroment->p,enviroment->l);
        std::cout<<"stemmed word: "<<stemmed<<std::endl;
        result.push_back(stemmed);
        std::cout<<"pushed"<<std::endl;
    }
    // For some reason, if I remove this, I get a segfault on the return.
    for (auto i: result){
    }
    return result;
}

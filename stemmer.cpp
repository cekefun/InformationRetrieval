//
// Created by cedric on 11/28/17.
//

#include "stemmer.h"
#include "stemmer/english.h"

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
        temp[str.size()] = 0;
        SN_set_current(enviroment,str.size(),temp);
        E_stem(enviroment);
        result.push_back(std::string(reinterpret_cast<char*>(temp)));
    }
    return result;
}
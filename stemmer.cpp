//
// Created by cedric on 11/28/17.
//
#include <iostream>
#include "stemmer.h"


std::vector<std::string> Stemmer::stem(const std::vector<std::string> &v) {
    std::vector<std::string> result;
    for(std::string str: v){
        std::wstring ws;
        ws.assign(str.begin(),str.end());
        StemEnglish(ws);
        std::string toAdd;
        toAdd.assign(ws.begin(),ws.end());
        result.push_back(toAdd);
    }
    return result;
}

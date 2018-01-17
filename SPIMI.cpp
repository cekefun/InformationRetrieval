//
// Created by cekef on 16-Jan-18.
//

#include "SPIMI.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#include <windows.h>
#define SYSERROR() GetLastError()

SPIMI::SPIMI(std::string dir): directoryname(dir) {}

void SPIMI::addFile(std::vector<std::string> f) {
    for(auto& i: f){
        dict[i].insert(docId);
    }
    if (sizeof(dict) > maxValue){
        flush("SPIMI"+std::to_string(nextFile)+"_1");
        nextFile++;
    }
    docId ++;
}

void SPIMI::flush(std::string filename) {
    std::ofstream ofs;
    ofs.open(directoryname+filename);
    for(auto i: dict) {
        // write the string
        ofs << i.first << " ";
        for (auto j: i.second) {
            ofs << std::to_string(j) << " ";
        }
        ofs << std::endl;
    }
    ofs.close();
    dict.clear();
}



bool SPIMI::load(std::string id, std::map<std::string,std::set<uint32_t >>& target) {
    target.clear();

    std::ifstream ifs;
    ifs.open(directoryname+id);
    if (!ifs.is_open()){
        return false;
    }
    std::string s;
    while (getline(ifs, s)) {
        std::set<uint32_t > values;
        std::istringstream f(s);
        std::string s2;
        std::string word;
        unsigned int temp = 0;
        while (getline(f,s2,' ')){
            if (temp == 0) {
                word = s2;
                temp++;
            }
            else {
                values.insert(std::atoi(s2.data()));
            }
        }
        target[word] = values;

    }
    ifs.close();
    return true;
}

void SPIMI::finish() {
    // flush first to make loop from beginning to end. It makes its easier to conceptualize
    if(!dict.empty()) {
        flush("SPIMI" + std::to_string(nextFile) + "_1");
        nextFile++;
    }
    combine(1,nextFile-1,true);
}

void SPIMI::print() {
    for(auto i: dict){
        std::cout<< i.first<<": ";
        for(auto j: i.second){
            std::cout<<j<<", ";
        }
        std::cout<<std::endl;
    }
}

void SPIMI::combine(uint32_t first, uint32_t second, bool nameFirst) {
    if (first + 1 < second) {
        int length = second - first;
        combine(first, first + length / 2, true);
        combine(first + length / 2 + 1, second, false);
    }
    if (first == second) {
        return;
    }
    actual_combine(first, second, nameFirst);
}

// This is so to minimize the amount of addresses will be allocated in during the recursive part
// Combines 2 disk indices to 1 disk index
void SPIMI::actual_combine(uint32_t first, uint32_t second, bool nameFirst) {
    unsigned int length = 1;
    std::string filename1 = "SPIMI"+std::to_string(first);
    std::string filename2 = "SPIMI"+std::to_string(second);
    std::string fileResult;
    if(nameFirst) {
        fileResult = filename1;
    }
    else {
        fileResult = filename2;
    }
    uint32_t n1 = 1;
    uint32_t n2 = 1;
    std::map<std::string,std::set<uint32_t >> dict1;
    std::map<std::string,std::set<uint32_t >> dict2;

    std::map<std::string,std::set<uint32_t >>::iterator it1;
    std::map<std::string,std::set<uint32_t >>::iterator it2;

    bool succes1 = false;
    bool succes2 = false;

    do{
        if (it1 == dict1.end()){
            succes1 = false;
        }
        if (it2 == dict2.end()){
            succes2 = false;
        }
        if(!succes1){
            succes1 = load(filename1+"_"+std::to_string(n1),dict1);
            remove((filename1+"_"+std::to_string(n1)).data());
            it1 = dict1.begin();
            n1++;
        }
        if(!succes2){
            succes2 = load(filename2+"_"+std::to_string(n2),dict2);
            remove((filename2+"_"+std::to_string(n2)).data());
            it2 = dict2.begin();
            n2++;
        }
        while((succes1 and succes2 and it2 != dict2.end() and it1 != dict1.end()) or (!succes1 and it2 != dict2.end()) or (!succes2 and it1 != dict1.end())){
            if (!succes2){
                dict[it1->first] = it1->second;
                it1++;
            }else if(!succes1){
                dict[it2->first] = it2->second;
                it2++;
            }
            else if(it1->first < it2->first){
                dict[it1->first] = it1->second;
                it1++;
            }
            else if(it2->first < it1->first){
                dict[it2->first] = it2->second;
                it2++;
            }
            else{
                dict[it1->first] = it1->second;
                dict[it2->first].insert(it2->second.begin(),it2->second.end());
                it1++;
                it2++;
            }

            if(sizeof(dict)>maxValue){
                flush("SPIMITEMP_" + std::to_string(length));
                length ++;
            }
        };
    }while(succes1 or succes2);
    if(!dict.empty()) {
        flush("SPIMITEMP_" + std::to_string(length));
        length ++;
    }

    for(unsigned int temp = 1; temp < length; temp++){
        std::rename(("SPIMITEMP_"+std::to_string(temp)).data(),(fileResult+"_"+std::to_string(temp)).data());
    }
}
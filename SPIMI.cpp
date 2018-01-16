//
// Created by cekef on 16-Jan-18.
//

#include "SPIMI.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

SPIMI::SPIMI(std::string dir): directoryname(dir) {}

void SPIMI::addFile(std::vector<std::string> f) {
    for(auto& i: f){
        dict[i].insert(docId);
    }
    std::cout<< sizeof(dict)<<std::endl;
    if (sizeof(dict) > maxValue){
        flush("SPIMI"+std::to_string(nextFile)+"_1");
        nextFile++;
    }
    docId ++;
}

void SPIMI::flush(std::string filename) {
    std::ofstream ofs;
    ofs.open(directoryname+filename);
    if(ofs.is_open()){
        std::cout<<"NOT OPEN"<<std::endl;
    }
    std::cout<< filename<<std::endl;
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
    flush("SPIMI"+std::to_string(nextFile)+"_1");
    unsigned int amount = nextFile;
    for(int i = 0; i < log2((double)nextFile); i++){
        for(uint32_t j = 1; j <= amount / 2 + amount % 2; j+=2){
            unsigned int length = 1;
            std::string filename1 = "SPIMI"+std::to_string(j);
            std::string filename2 = "SPIMI"+std::to_string(j+1);
            uint32_t n1 = 1;
            uint32_t n2 = 1;
            std::map<std::string,std::set<uint32_t >> dict1;
            std::map<std::string,std::set<uint32_t >> dict2;

            std::map<std::string,std::set<uint32_t >>::iterator it1;
            std::map<std::string,std::set<uint32_t >>::iterator it2;

            bool succes1 = false;
            bool succes2 = false;

            do{
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
                while(!((it1 == dict1.end() and succes1) or (it2 == dict2.end() and succes2))){
                    if(!succes2 or it1->first < it2->first){
                        dict[it1->first] = it1->second;
                        it1++;
                    }
                    else if(!succes1 or it1->first > it2->first){
                        dict[it2->first] = it2->second;
                        it2++;
                    }
                    //it1->first == it2->first
                    else if(succes1 and succes2){
                        dict[it1->first] = it1->second;
                        dict[it2->first].insert(it2->second.begin(),it2->second.end());
                        it1++;
                        it2++;
                    }
                    if(sizeof(dict)> maxValue){
                        flush("SPIMI"+std::to_string(j)+"_"+std::to_string(length));
                        length++;
                    }
                }

            }while(succes1 or succes2);
            flush("SPIMI"+std::to_string(j)+"_"+std::to_string(length));

        }
        amount = amount / 2 + amount % 2;
    }
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
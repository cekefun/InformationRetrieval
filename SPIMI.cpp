//
// Created by cekef on 16-Jan-18.
//

#include "SPIMI.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <stdlib.h>

#if _WIN32
#include <windows.h>

#endif

SPIMI::SPIMI() {
    directoryName ="SPIMI";
#ifdef _WIN32
    CreateDirectory(directoryName.c_str(),NULL);

#elif __linux__
    mkdir(directoryName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
}

void SPIMI::addFile(std::vector<std::string> f) {
    for(auto& i: f){
        if(dict.find(i) == dict.end()){
            currentSize += i.size();
        }
        if(dict[i].insert(docId).second){
            currentSize +=4;
        }
    }
    if (currentSize > maxValue){
        flush("SPIMI"+std::to_string(nextFile)+"_1");
        nextFile++;
    }
    docId ++;
}

void SPIMI::flush(std::string filename) {
    std::ofstream ofs;
    ofs.open(directoryName+"/"+filename);
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
    currentSize = 0;
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

void SPIMI::combine(unsigned int first, unsigned int second, bool nameFirst) {
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
void SPIMI::actual_combine(unsigned int first, unsigned int second, bool nameFirst) {
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
    unsigned int n1 = 1;
    unsigned int n2 = 1;

    bool succes1 = false;
    bool succes2 = false;

    std::string line1;
    std::string line2;

    std::string word1;
    std::set<uint32_t > set1;

    std::string word2;
    std::set<uint32_t > set2;

    std::ifstream f1;
    std::ifstream f2;

    do{
        if (f1.peek() == EOF){
            succes1 = false;
            remove((directoryName+'/'+filename1+"_"+std::to_string(n1-1)).c_str());
        }
        if (f2.peek() == EOF){
            succes2 = false;
            remove((directoryName+'/'+filename2+"_"+std::to_string(n2-1)).c_str());
        }
        if(!succes1){
            f1.open(directoryName+'/'+filename1+"_"+std::to_string(n1));
            succes1 = f1.is_open();
            if (succes1){
                getline(f1,line1);
                ParseLine(line1,word1,set1);
            }
            n1++;
        }
        if(!succes2){
            f2.open(directoryName+'/'+filename2+"_"+std::to_string(n2));
            succes2 = f2.is_open();
            if (succes2){
                getline(f2,line2);
                ParseLine(line2,word2,set2);

            }
            n2++;
        }
        while((succes1 and succes2 and f1.peek()!=EOF and f2.peek() != EOF) or (!succes1 and f2.peek() != EOF) or (!succes2 and f1.peek() != EOF)){
            if (!succes2){
                dict[word1] = set1;
                currentSize += word1.size() + 4*set1.size();
                getline(f1,line1);
                ParseLine(line1,word1,set1);
            }else if(!succes1){
                dict[word2] = set2;
                currentSize += word2.size() + 4*set2.size();
                getline(f2,line2);
                ParseLine(line2,word2,set2);
            }
            else if(word1 < word2){
                dict[word1] = set1;
                currentSize += word1.size() + 4*set1.size();
                getline(f1,line1);
                ParseLine(line1,word1,set1);
            }
            else if(word2 < word1){
                dict[word2] = set2;
                currentSize += word2.size() + 4*set2.size();
                getline(f2,line2);
                ParseLine(line2,word2,set2);
            }
            else{
                dict[word1] = set1;
                dict[word1].insert(set2.begin(),set2.end());
                currentSize += word1.size() + 4*set1.size() + 4*set2.size();
                getline(f1,line1);
                ParseLine(line1,word1,set1);
                getline(f2,line2);
                ParseLine(line2,word2,set2);
            }

            if(currentSize> maxValue){
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

void SPIMI::ParseLine(std::string line,std::string& target,std::set<uint32_t >& targetSet) {
    target.clear();
    targetSet.clear();
    std::istringstream f(line);
    unsigned int temp = 0;
    std::string token;
    while (getline(f,token,' ')) {
        if (temp == 0) {
            target = token;
            temp++;
        } else {
            targetSet.insert(std::atoi(token.data()));
        }
    }
}
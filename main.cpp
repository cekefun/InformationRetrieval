#include <iostream>
#include <cstring>
#include <vector>
#include "stemmer.h"
#include "SPIMI.h"

Stemmer stemmer;
SPIMI spimi;


void handleFile(std::string& filestring){
    std::cout<<"tokenizing"<<std::endl;
    char* pch = std::strtok(&filestring[0u]," .,!?@#$%^&*_-`~+=:;|<>'\"(){}[]\\/");
    std::vector<std::string> Tokens;
    while(pch != NULL){
        std::string word = pch;
        for(int i =0; i < word.size(); ++i){
            word[i] = tolower(word[i]);
        }
        Tokens.push_back(word);
        pch = strtok(NULL," .,'");
    }
    //free memory
    filestring.clear();
    std::vector<std::string> stemmed;
    std::cout<<"stemming"<<std::endl;
    stemmed = stemmer.stem(Tokens);

    std::cout<<"ADDING FILE"<<std::endl;
    spimi.addFile(stemmed);
}

int main() {
    //"../Wikipedia/enwiki-20170820-pages-articles.xml"
    stemmer = Stemmer();
    spimi = SPIMI();


//    sp.finish();
    return 0;
}



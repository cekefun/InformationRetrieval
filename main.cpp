#include <iostream>
#include <cstring>
#include <vector>
#include "stemmer.h"
#include "SPIMI.h"
#include "Markup/Markup.h"

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
    CMarkup WikiReader;
    bool loadsucces = WikiReader.Load("../tempSet.xml");
    if(!loadsucces){
        std::cout<<"FILE NOT FOUND"<<std::endl;
        return -1;
    }
    WikiReader.FindElem();
    WikiReader.IntoElem();
    while(WikiReader.FindElem("page")) {
        WikiReader.IntoElem();
        WikiReader.FindElem("revision");
        WikiReader.IntoElem();
        WikiReader.FindElem("text");
        std::string info = WikiReader.GetData();
        handleFile(info);
        WikiReader.OutOfElem();
        WikiReader.OutOfElem();
    }

//    sp.finish();
    return 0;
}



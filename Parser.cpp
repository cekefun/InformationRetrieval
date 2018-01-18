//
// Created by cekef on 18-Jan-18.
//

#include "Parser.h"
#include <iostream>
#include <cstring>

Parser::Parser() {
    stemmer = Stemmer();
    spimi = SPIMI();
}

void Parser::OnPostCreate() {
    EnableStartElementHandler ();
    EnableEndElementHandler ();
    // Note: EnableElementHandler will do both start and end
    EnableCharacterDataHandler ();
}

void Parser::OnStartElement(const XML_Char *tagname, const XML_Char **) {
    std::string temp(tagname);
    if(temp == "text"){
        InText = true;
    }

}

void Parser::OnEndElement(const XML_Char *tagname) {
    if(InText) {
        InText = false;
        //std::cout<<currentFile<<std::endl;
        handleFile();
    }
}

void Parser::OnCharacterData(const XML_Char *pszData, int nLength) {
    if(InText){
        std::string filePiece(pszData,nLength);
        currentFile.append(filePiece);
    }
}

void Parser::handleFile(){

    for(int i =0; i < currentFile.size(); i++){
        if(isalpha(currentFile[i])){
            currentFile[i] = tolower(currentFile[i]);
        } else{
            currentFile[i] = ' ';
        }
    }

    char* pch = std::strtok(&currentFile[0u]," ");
    std::vector<std::string> Tokens;
    while(pch != NULL){
        std::string word = pch;
        if(!word.empty()){
            Tokens.push_back(word);
        }
        pch = strtok(NULL," ");
    }
    //free memory
    currentFile.clear();
//    std::cout<<"TOKENS: "<<std::endl;
//    for(auto i: Tokens){
//        std::cout<<i<<std::endl;
//    }
//    std::cout<<std::endl;
//
//
//    std::vector<std::string> stemmed;
//    std::cout<<"stemming"<<std::endl;
//    stemmed = stemmer.stem(Tokens);

    //std::cout<<"ADDING FILE"<<std::endl;
    spimi.addFile(Tokens);
}

void Parser::finishSPIMI() {
    spimi.finish();
}
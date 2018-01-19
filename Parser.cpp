//
// Created by cekef on 18-Jan-18.
//

#include <sstream>

#include "Parser.h"

#include "BSBI/bsbi.h"

Parser::Parser(unsigned int amount_of_documents):
        maxDocuments(amount_of_documents)
{
#ifdef USESPIMI
         spimi = SPIMI();
#else
         enableBSBI();
#endif
    currentDocumentId = 0;
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
    currentDocumentId++;

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
            if(stopwords[word]){
                Tokens.push_back(word);
            }
        }
        pch = strtok(NULL," ");
    }
    //free memory
    currentFile.clear();

    std::vector<std::string> stemmed;
    stemmed = stemmer.stem(Tokens);
    Tokens.clear();
    
#ifdef  USESPIMI
    spimi.addFile(stemmed);
#else
    std::stringstream ss;
    for(auto& s : stemmed) {
        ss << s << " ";
    }
    indexDocument(currentDocumentId, ss);
#endif
}

void Parser::finish() {
#if USESPIMI
        spimi.finish();
#else
        finalizeBSBI();
#endif
}

bool Parser::keepGoing(){
    return currentDocumentId < maxDocuments;
}
//
// Created by cekef on 18-Jan-18.
//

#include <ctime>
#include "expath/ExpatImpl.h"
#include "stemmer.h"
#include "SPIMI.h"
#include "StopWords.h"

#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H


class Parser: public CExpatImpl<Parser> {
public:
    Parser(unsigned int amount_of_documents = -1);

    void OnPostCreate();

    void OnStartElement(const XML_Char *, const XML_Char **);

    void OnEndElement(const XML_Char *);

    void OnCharacterData(const XML_Char *pszData, int nLength);

    void finish();

    bool keepGoing();

    void printStats();

private:
    Stemmer stemmer;
    SPIMI spimi;
    bool InText = false;
    std::string currentFile;
    StopWords stopwords;
    unsigned int currentDocumentId;
    unsigned int maxDocuments;
    std::clock_t start;
    std::clock_t end;

    void handleFile();
};


#endif //PROJECT_PARSER_H

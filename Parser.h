//
// Created by cekef on 18-Jan-18.
//

#include "expath/ExpatImpl.h"
#include "stemmer.h"
#include "SPIMI.h"
#include "StopWords.h"

#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H


class Parser: public CExpatImpl<Parser> {
public:
    Parser();

    void OnPostCreate();

    void OnStartElement(const XML_Char *, const XML_Char **);

    void OnEndElement(const XML_Char *);

    void OnCharacterData(const XML_Char *pszData, int nLength);

    void finishSPIMI();

private:
    Stemmer stemmer;
    SPIMI spimi;
    bool InText = false;
    std::string currentFile;
    StopWords stopwords;

    void handleFile();
};


#endif //PROJECT_PARSER_H

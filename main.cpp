#include <iostream>
#include <winnt.h>
#include "Parser.h"


int main() {
    //"../Wikipedia/enwiki-20170820-pages-articles.xml"
    Parser myParser;
    if(!myParser.Create()){
        std::cout<<"FAILED TO CREATE PARSER"<<std::endl;
        return -1;
    }

    //FILE *fp = fopen("../tempSet.xml","r");
    FILE *fp = fopen("../Wikipedia/enwiki-20170820-pages-articles.xml","r");
    if(fp == NULL){
        std::cout <<"FAILED TO OPEN THE FILE"<<std::endl;
        return -1;
    }

    bool fSuccess = true;
    while (!feof (fp) && fSuccess)
    {
        LPSTR pszBuffer = (LPSTR) myParser .GetBuffer (256); // REQUEST
        if (pszBuffer == NULL)
            fSuccess = false;
        else
        {
            int nLength = fread (pszBuffer, 1, 256, fp); // READ
            fSuccess = myParser .ParseBuffer (nLength, nLength == 0); // PARSE
        }
    }
    myParser.finishSPIMI();
    // Close the file

    fclose (fp);
    return fSuccess;
//    sp.finish();
    return 0;
}



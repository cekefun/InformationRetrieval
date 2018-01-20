#include <iostream>
#include "Parser.h"


int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Please give a filename" << std::endl;
        return -1;
    }
    int i = -1;
    if(argc > 2){
        i = std::atoi(argv[2]);
    }
    //"../Wikipedia/enwiki-20170820-pages-articles.xml"
    Parser myParser(i);
    if(!myParser.Create()){
        std::cout<<"FAILED TO CREATE PARSER"<<std::endl;
        return -1;
    }

    //FILE *fp = fopen("../tempSet.xml","r");
    FILE *fp = fopen(argv[1],"r");
    if(fp == NULL){
        std::cout <<"FAILED TO OPEN THE FILE"<<std::endl;
        return -1;
    }

    bool fSuccess = true;
    while (!feof (fp) && fSuccess && myParser.keepGoing())
    {
        char* pszBuffer = (char*) myParser .GetBuffer (1024); // REQUEST
        if (pszBuffer == NULL)
            fSuccess = false;
        else
        {
            int nLength = fread (pszBuffer, 1, 1024, fp); // READ
            fSuccess = myParser .ParseBuffer (nLength, nLength == 0); // PARSE
        }
    }
    myParser.finish();
    // Close the file

    fclose (fp);
    myParser.printStats();
    return fSuccess;
//    sp.finish();
}


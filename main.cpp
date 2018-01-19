#include <iostream>
#include "Parser.h"


int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Please give a filename" << std::endl;
        return -1;
    }

    bool useBSBI = false;
    if(argc > 2) {
        if(argv[2][0] == '1') {
            useBSBI = true;
        }
    }

    //"../Wikipedia/enwiki-20170820-pages-articles.xml"
    Parser myParser(useBSBI);
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
    while (!feof (fp) && fSuccess)
    {
        char* pszBuffer = (char*) myParser .GetBuffer (256); // REQUEST
        if (pszBuffer == NULL)
            fSuccess = false;
        else
        {
            int nLength = fread (pszBuffer, 1, 256, fp); // READ
            fSuccess = myParser .ParseBuffer (nLength, nLength == 0); // PARSE
        }
    }
    myParser.finish();
    // Close the file

    fclose (fp);
    return fSuccess;
//    sp.finish();
    return 0;
}



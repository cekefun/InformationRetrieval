#include <iostream>
#include <cstring>
#include <vector>
#include <expat.h>
#include "stemmer.h"
void XMLCALL enterElement(void *data, const char* el, const char **attr){
    std::string element = el;
    std::cout<<element<<std::endl;
}

void XMLCALL leaveElement(void *data, const char* el){
    std::string element = el;
    std::cout<<"/"<<element<<std::endl;
}

void XMLCALL Datahandler(void * userData, const XML_Char *s, int len){
    std::cout<<s[0]<<s[len-1]<<std::endl;
}

int main() {
    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser,enterElement,leaveElement);
    XML_SetCharacterDataHandler(parser,Datahandler);
    FILE *fp = fopen("tempSet.xml","r");
    XML_Parse(parser,buf,)
    std::string testString = "This string is to test our stemmer. Hopefully it will work.";
    char* pch = std::strtok(&testString[0u]," .,'");
    std::vector<std::string> Tokens;
//    while(pch != NULL){
//        std::string word = pch;
//        for(int i =0; i < word.size(); ++i){
//            word[i] = tolower(word[i]);
//        }
//        Tokens.push_back(word);
//        pch = strtok(NULL," .,'");
//    }
//    std::cout<<"Original tokens:"<<std::endl;
//    for(auto i: Tokens){
//        std::cout<<i<<std::endl;
//    }
//    Stemmer stemmer= Stemmer();
//    std::vector<std::string> stemmed;
//    stemmed = stemmer.stem(Tokens);
//    std::cout<<"Stemmed tokens:"<<std::endl;
//    for (auto i: stemmed)
//        std::cout<<i<<std::endl;
    return 0;
}


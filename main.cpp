#include <iostream>
#include <cstring>
#include <vector>
#include <expat.h>
#include "stemmer.h"

Stemmer stemmer;
void XMLCALL enterElement(void *data, const char* el, const char **attr){
    bool* toIndex = (bool *) data;
    std::string element = el;
    if (element == "text"){
        *toIndex = true;
    }
    std::cout<<element<<std::endl;
}

void XMLCALL leaveElement(void *data, const char* el){
    bool* toIndex = (bool *) data;
    *toIndex = false;
    std::string element = el;
    std::cout<<"/"<<element<<std::endl;
}

void XMLCALL Datahandler(void * userData, const XML_Char *s, int len){
    std::cout<<s[0]<<s[len-1]<<std::endl;
}

//int main() {
//    XML_Parser parser = XML_ParserCreate(NULL);
//    XML_SetElementHandler(parser,enterElement,leaveElement);
//    XML_SetCharacterDataHandler(parser,Datahandler);
//    FILE *fp = fopen("tempSet.xml","r");
//    fseek(fp,0L,SEEK_END);
//    auto size = ftell(fp);
//    rewind(fp);
//    XML_Parse(parser,fp,size,0);
//
//    std::string testString = "This string is to test our stemmer. Hopefully it will work.";
//    char* pch = std::strtok(&testString[0u]," .,'");
//    std::vector<std::string> Tokens;
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
//    return 0;
//}

int
main(int argc, char *argv[])
{
    stemmer = Stemmer();
    char buf[BUFSIZ];
    std::cout<<"HERE"<<std::endl;
    XML_Parser parser = XML_ParserCreate(nullptr);
    int done;
    bool index = false;
    (void)argc;
    (void)argv;

    XML_SetUserData(parser, &index);
    XML_SetElementHandler(parser, enterElement, leaveElement);
    XML_SetCharacterDataHandler(parser,Datahandler);
    FILE *fp = fopen("tempSet.xml","r");
    do {
        size_t len = fread(buf, 1, sizeof(buf), fp);
        done = len < sizeof(buf);
        if (XML_Parse(parser, buf, (int)len, done) == XML_STATUS_ERROR) {
            std::cout<<"ERROR"<<std::endl;
            return 1;
        }
    } while (!done);
    XML_ParserFree(parser);
    std::cout<<"exit"<<std::endl;
    return 0;
}



#include <iostream>
#include <cstring>
#include <vector>
#include "stemmer.h"

int main() {

    std::string testString = "This string is to test our stemmer. Hopefully it will work.";
    char* pch = std::strtok(&testString[0u]," .,'");
    std::vector<std::string> Tokens;
    while(pch != NULL){
        std::string word = pch;
        for(int i =0; i < word.size(); ++i){
            word[i] = tolower(word[i]);
        }
        Tokens.push_back(word);
        pch = strtok(NULL," .,'");
    }
    std::cout<<"Original tokens:"<<std::endl;
    for(auto i: Tokens){
        std::cout<<i<<std::endl;
    }
    Stemmer stemmer= Stemmer();
    std::vector<std::string> stemmed;
    stemmed = stemmer.stem(Tokens);
    std::cout<<"Stemmed tokens:"<<std::endl;
    for (auto i: stemmed)
        std::cout<<i<<std::endl;
    return 0;
}




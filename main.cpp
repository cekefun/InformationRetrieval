#include <iostream>
#include <cstring>
#include <vector>
#include "stemmer.h"
#include "SPIMI.h"

int main() {

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

    std::vector<std::string> doc1 = {"bla","bla","bla","first","document","test","document","make","this","country","great","again"};
    std::vector<std::string> doc2 = {"this","is","the","second","test","document"};
    SPIMI sp;
    sp.addFile(doc1);
    sp.print();
    sp.flush("test.txt");
    //sp.addFile(doc2);
    //sp.print();

    return 0;
}




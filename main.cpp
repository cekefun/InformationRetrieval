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
    std::vector<std::string> doc3 = {"document","three","is","here","to","stay"};
    std::vector<std::string> doc4 = {"this","document","is","the","greatest","and","biggest","document","it","is","great","it","is","the","best"};
    std::vector<std::string> doc5 = {"document","the","fifth","is","a","good","boy"};
    std::vector<std::string> doc6 = {"doc","is","shorter","than","the","word","document"};
    std::vector<std::string> doc7 = {"the","last","doc","is","document","number","seven"};

    SPIMI sp;
    sp.addFile(doc1);
    sp.addFile(doc2);
    sp.addFile(doc3);
    sp.addFile(doc4);
    sp.addFile(doc5);
    sp.addFile(doc6);
    sp.addFile(doc7);

    sp.finish();

    return 0;
}




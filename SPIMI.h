//
// Created by cekef on 16-Jan-18.
//

#include <vector>
#include <string>
#include <map>
#include <set>
#ifndef PROJECT_SPIMI_H
#define PROJECT_SPIMI_H


class SPIMI {
public:
    SPIMI(std::string dir="");
    void addFile(std::vector<std::string>);
    void finish();
    void print();

    void flush(std::string);
    bool load(std::string,std::map<std::string,std::set<uint32_t >>&);

private:
    uint32_t docId =0;
    uint32_t nextFile = 1;
    std::map<std::string, std::set<uint32_t >> dict;
    std::string directoryname;

    uint32_t maxValue = 1073741824;
};


#endif //PROJECT_SPIMI_H

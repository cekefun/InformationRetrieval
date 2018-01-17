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
    SPIMI(std::string dir = "");

    void addFile(std::vector<std::string>);

    void finish();

    void print();

private:
    uint32_t docId = 0;
    uint32_t nextFile = 1;
    std::map<std::string, std::set<uint32_t >> dict;
    std::string directoryname;
    // GIVE A BETTER VALUE
    uint32_t maxValue = 1048576;

    void combine(uint32_t, uint32_t, bool);

    void actual_combine(uint32_t, uint32_t, bool);

    void flush(std::string);

    bool load(std::string, std::map<std::string, std::set<uint32_t >> &);

};


#endif //PROJECT_SPIMI_H

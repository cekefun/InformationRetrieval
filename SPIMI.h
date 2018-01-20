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
    SPIMI();

    void addFile(std::vector<std::string>);

    void finish();

    void print();


private:
    unsigned int docId = 0;
    unsigned int nextFile = 1;
    std::map<std::string, std::set<unsigned int >> dict;
    // GIVE A BETTER VALUE
    unsigned int maxValue = 1024*1024*250; // 250 MB

    void combine(unsigned int, unsigned int, bool);

    void actual_combine(unsigned int, unsigned int, bool);

    void flush(std::string);

    unsigned int currentSize;

    std::string directoryName;

    void ParseLine(std::string, std::string&, std::set<uint32_t >&);
};

#endif //PROJECT_SPIMI_H

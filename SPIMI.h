//
// Created by cekef on 16-Jan-18.
//

#include <vector>
#include <string>
#include <map>
#include <set>

#if _WIN32
#include <windows.h>
#include <psapi.h>
#endif

#ifndef PROJECT_SPIMI_H
#define PROJECT_SPIMI_H


class SPIMI {
public:
    SPIMI(std::string dir = "");

    void addFile(std::vector<std::string>);

    void finish();

    void print();

private:
    unsigned int docId = 0;
    unsigned int nextFile = 1;
    std::map<std::string, std::set<unsigned int >> dict;
    std::string directoryname;
    // GIVE A BETTER VALUE
    unsigned int maxValue = 1073741824; // 1 GB
#if _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
#endif

    void combine(unsigned int, unsigned int, bool);

    void actual_combine(unsigned int, unsigned int, bool);

    void flush(std::string);

    bool load(std::string, std::map<std::string, std::set<unsigned int >> &);

    unsigned int currentSize;



};
#ifdef __linux__
int parseLine(char*);
#endif

#endif //PROJECT_SPIMI_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstddef>
#include <map>
#include <cmath>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <vector>
#include <queue>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
  std::string directoryName;
  if(argc != 2) {
    return 0;
  }

  directoryName = argv[1];
  std::map<uint32_t, std::string> terms;

  std::ifstream termsIfs;
  termsIfs.open(directoryName + "/terms", std::ofstream::binary);
  char buffer[256];
  while(termsIfs.good()) {
    uint32_t termId = 0;
    uint8_t strLength = 0;
    termsIfs.read(reinterpret_cast<char*>(&termId), sizeof(termId));
    termsIfs.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
    termsIfs.read(buffer, strLength);
    buffer[strLength] = '\0';
    terms[termId] = buffer;
  }

  termsIfs.close();

  std::ifstream indexIfs;
  indexIfs.open(directoryName + "/index", std::ofstream::binary);
  while(indexIfs.good()) {
    uint32_t termId = 0;
    uint32_t documentCount = 0;
    indexIfs.read(reinterpret_cast<char*>(&termId), sizeof(termId));
    indexIfs.read(reinterpret_cast<char*>(&documentCount), sizeof(documentCount));

    std::cout << terms[termId] << ": ";
    for(uint32_t i = 0; i < documentCount; i++) {
      uint32_t docId;
      indexIfs.read(reinterpret_cast<char*>(&docId), sizeof(docId));
      std::cout << docId;
      if(i+1 < documentCount) {
        std::cout << ", ";
      }
    }
    std::cout << std::endl;
  }
  indexIfs.close();

}

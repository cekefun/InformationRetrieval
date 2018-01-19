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

std::string directoryName;

const std::string getDateTime()
{
  time_t now = time(0);
  tm tstruct = *localtime(&now);
  char buf[128];
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return buf;
}

struct TDRecord
{
  TDRecord(uint32_t termId, uint32_t docId)
    : termId(termId), docId(docId)
    {
    }

  uint32_t termId;
  uint32_t docId;
};

const size_t BLOCK_SIZE = 1024*1024;
const size_t TD_RECORDS_PER_BLOCK = BLOCK_SIZE / sizeof(TDRecord);

std::map<std::string, uint32_t> terms;

bool getToken(std::istream& ifs, std::string& token)
{
  std::string tmp;
  if(!ifs.good()) {
    return false;
  }

  ifs >> tmp;
  if(tmp.length() == 0) {
    return false;
  }

  token = tmp;
  return true;
}




struct Block
{
  Block()
    : nRecords(0), tdRecords(nullptr)
    {
    }

  uint32_t nRecords;
  TDRecord* tdRecords;

  bool addTD(uint32_t termId, uint32_t docId)
  {
    if(this->nRecords >= TD_RECORDS_PER_BLOCK) {
      return false;
    }

    *(this->tdRecords + nRecords) = TDRecord(termId, docId);
    this->nRecords++;

    return true;
  }

  bool isFull()
  {
    return this->nRecords >= TD_RECORDS_PER_BLOCK;
  }

  void sort()
  {
    /*std::cout << "SORTING" << std::endl;
    for(int i = 0; i < this->nRecords; i++) {
      std::cout << "(" << (this->tdRecords+i)->termId << ", " << (this->tdRecords+i)->docId << ")" << std::endl;
    }*/


    std::stable_sort(this->tdRecords, this->tdRecords + this->nRecords, [](const TDRecord& a, const TDRecord& b) {
      return a.termId < b.termId;
    });

    /*std::cout << "SORTING DONE" << std::endl;
    for(uint32_t i = 0; i < this->nRecords; i++) {
      std::cout << "(" << (this->tdRecords+i)->termId << ", " << (this->tdRecords+i)->docId << ")" << std::endl;
    }*/
  }

  void toDisk(size_t id)
  {
    std::ofstream ofs;
    ofs.open(directoryName + "/" + std::to_string(id), std::ofstream::binary);

    size_t i = 0;
    while(i < this->nRecords) {
      TDRecord* curRecord = (this->tdRecords + i);
      TDRecord* prevRecord = curRecord;
      uint32_t documentCounter = 0;
      //std::cout << "Starting at term " << curRecord->termId << std::endl;
      ofs.write(reinterpret_cast<char*>(&curRecord->termId), sizeof(curRecord->termId));
      auto documentCounterPos = ofs.tellp();
      ofs.write(reinterpret_cast<char*>(&documentCounter), sizeof(documentCounter)); // Placeholder

      while(curRecord != nullptr && curRecord->termId == prevRecord->termId) {
        if(prevRecord != curRecord && prevRecord->docId == curRecord->docId) {
          i++;
          if(i >= this->nRecords) {
            prevRecord = curRecord;
            curRecord = nullptr;
          } else {
            curRecord++;
            prevRecord++;
          }
          continue;
        }

        ofs.write(reinterpret_cast<char*>(&curRecord->docId), sizeof(curRecord->docId));
        //std::cout << "Added document " << curRecord->docId << std::endl;
        documentCounter++;

        i++;
        if(i >= this->nRecords) {
          prevRecord = curRecord;
          curRecord = nullptr;
        } else {
          if(curRecord == prevRecord) {
            curRecord++;
          }  else {
            curRecord++;
            prevRecord++;
          }
        }
      }

      // Now we fill in how many documents for this term.
      auto currentPos = ofs.tellp();
      ofs.seekp(documentCounterPos);
      ofs.write(reinterpret_cast<char*>(&documentCounter), sizeof(documentCounter));
      ofs.seekp(currentPos);

      //ofs << std::endl;


    }

    ofs.close();
  }

};

void allocateBlock(Block& block)
{
  if(block.tdRecords == nullptr) {
    //freeBlock(block);
    block.tdRecords = reinterpret_cast<TDRecord*>(operator new(BLOCK_SIZE));
  }

  block.nRecords = 0;

}

void freeBlock(Block& block)
{
  operator delete(static_cast<void*>(block.tdRecords));
  block.tdRecords = nullptr;
}


bool parseNextBlock(Block& block, uint32_t docId, std::istream& ifs)
{
  std::string token;
  while(true) {
    if(block.isFull()) {
      return false;
    }

    if(!getToken(ifs, token)) {
      return true;
    }

    auto pair = terms.insert(std::pair<std::string, uint32_t>(token, terms.size()+1));
    block.addTD(pair.first->second, docId);
  }
}

void mergeBlocks(size_t last)
{
  std::ofstream mergedBlocks;
  mergedBlocks.open(directoryName + "/index", std::ofstream::binary);

  std::vector<std::ifstream*> streams;

  for(size_t i = 0; i < last; i++) {
    std::ifstream* ifs = new std::ifstream;
    ifs->open(directoryName + "/" + std::to_string(i), std::ofstream::binary);
    streams.push_back(ifs);
  }

  uint32_t currentTermId = 1;
  while(true) {

    std::priority_queue<uint32_t, std::vector<uint32_t>, std::greater<uint32_t>> documentIds;

    for(size_t i = 0; i < streams.size(); i++) {
      uint32_t termId = 0;
      auto currentPos = streams[i]->tellg();
      streams[i]->read(reinterpret_cast<char*>(&termId), sizeof(termId));
      if(currentTermId != termId) {
        streams[i]->seekg(currentPos);
        continue;
      }

      uint32_t documentCount = 0;
      streams[i]->read(reinterpret_cast<char*>(&documentCount), sizeof(documentCount));
      for(uint32_t j = 0; j < documentCount; j++) {
        uint32_t docId = 0;
        streams[i]->read(reinterpret_cast<char*>(&docId), sizeof(docId));
        documentIds.push(docId);
      }

      //documentCounts.push_back(documentCount);
    }


    if(documentIds.size() == 0) {
      break;
    } else {
      mergedBlocks.write(reinterpret_cast<char*>(&currentTermId), sizeof(uint32_t));
      uint32_t documentCount = documentIds.size();
      uint32_t realDocumentCount = 0;
      auto realDocumentCountPos = mergedBlocks.tellp();
      mergedBlocks.write(reinterpret_cast<char*>(&realDocumentCount), sizeof(uint32_t)); // Placeholder
      uint32_t prevDocId = documentIds.top();
      bool firstSeen = true;
      while(!documentIds.empty()) {
        uint32_t docId = documentIds.top();
        documentIds.pop();

        if(prevDocId == docId && !firstSeen) {
          continue;
        }

        firstSeen = false;
        prevDocId = docId;
        mergedBlocks.write(reinterpret_cast<char*>(&docId), sizeof(uint32_t));
        realDocumentCount++;
      }

      auto curPos = mergedBlocks.tellp();
      mergedBlocks.seekp(realDocumentCountPos);
      mergedBlocks.write(reinterpret_cast<char*>(&realDocumentCount), sizeof(uint32_t));
      mergedBlocks.seekp(curPos);
    }

    currentTermId++;
  }


  for(size_t i = 0; i < streams.size(); i++) {
    streams[i]->close();
  }

  mergedBlocks.close();
}

size_t blockCounter;
Block block;

void enableBSBI()
{
  std::cout << "STATISTICS" << std::endl;
  std::cout << "----------" << std::endl;
  std::cout << "BLOCK SIZE: " << BLOCK_SIZE << " bytes." << std::endl;
  std::cout << "# OF PAIRS PER BLOCK: " << TD_RECORDS_PER_BLOCK << "." << std::endl;
  std::cout << "---------" << std::endl;

  directoryName = getDateTime();
  mkdir(directoryName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

  allocateBlock(block);
  blockCounter = 0;
}

void indexDocument(unsigned int docId, std::istream& terms)
{
    while(terms.good()) {
      if(!parseNextBlock(block, docId, terms)) {

        block.sort();
        block.toDisk(blockCounter);
        allocateBlock(block);
        blockCounter++;
      }
    }
}

void finalizeBSBI()
{
  block.sort();
  block.toDisk(blockCounter);
  blockCounter++;
  freeBlock(block);

  mergeBlocks(blockCounter);
  std::ofstream termsOfs;
  termsOfs.open(directoryName + "/terms", std::ofstream::binary);
  if(!termsOfs.is_open()) {
  }
  for(auto& it : terms) {

    uint32_t termId = it.second;
    uint8_t strLength = it.first.size();
    termsOfs.write(reinterpret_cast<char*>(&termId), sizeof(termId));
    termsOfs.write(reinterpret_cast<char*>(&strLength), sizeof(strLength));
    termsOfs.write(it.first.c_str(), strLength);
  }
  termsOfs.close();
}

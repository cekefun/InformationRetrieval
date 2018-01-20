#ifndef BSBI_H
#define BSBI_H

#include <istream>

void enableBSBI();
void indexDocument(unsigned int docId, std::istream& terms);
void finalizeBSBI();

#endif
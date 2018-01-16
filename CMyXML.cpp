//
// Created by cekef on 11-Dec-17.
//

#include "ExpatImpl.h"
#include <iostream>

#ifndef PROJECT_CMYXML_H
#define PROJECT_CMYXML_H

class CMyXML : public CExpatImpl <CMyXML>
{
public:

// Constructor

CMyXML ()
{
}

// Invoked by CExpatImpl after the parser is created

void OnPostCreate ()
{
    // Enable all the event routines we want
    EnableStartElementHandler ();
    EnableEndElementHandler ();
    // Note: EnableElementHandler will do both start and end
    EnableCharacterDataHandler ();
}

// Start element handler

void OnStartElement (const XML_Char *pszName, const XML_Char **papszAttrs)
{

    printf ("We got a start element %s\n", pszName);
    return;
}

// End element handler

void OnEndElement (const XML_Char *pszName)
{
    printf ("We got an end element %s\n", pszName);
    return;
}

// Character data handler

void OnCharacterData (const XML_Char *pszData, int nLength)
{
    // note, pszData is NOT null terminated
    printf ("We got %d bytes of data\n", nLength);
    return;
}
};
#endif //PROJECT_CMYXML_H

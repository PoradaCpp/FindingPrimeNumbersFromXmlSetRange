/**
  *************************************************************************************************************************
  * @file    readxml.h
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    23-November-2018
  * @brief   Class for xml files parsing
  *
  *          File .xml must have the same structure:
  *
  *          <root>
  *             <circles>
  *                 <circle>
  *                     <center_x> 250 </center_x>
  *                     <center_y> 250 </center_y>
  *                     <radius> 100 </radius>
  *                 </circle>
  *
  *                 <circle>
  *                     <center_x> 280 </center_x>
  *                     <center_y> 270 </center_y>
  *                     <radius> 10</radius>
  *                 </circle>
  *             </circles>
  *         </root>
  *
  *************************************************************************************************************************
*/

#ifndef READXML_H
#define READXML_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "tag.h"
#include "interval.hpp"

class XML_output;

class AddressNotExist {};                                                    // Class for throwing search error exception

class ReadXml
{
public:
    ReadXml(const char *pFileName, std::vector <std::string> Address = std::vector <std::string> ());
    ~ReadXml();

    Tag getTag(size_t &nCurPos, std::string sName) const;
    uint32_t findData(std::vector < std::string > Address) const;           // Data searching from parsed xml
    void setOutput(XML_output *pOut);
    void output() const;

private:    
    static constexpr const char *m_pDelim = "<>,./ \n\t\r\'\"";              // Delimetres for parsing

    VectorTagShared m_tagVc;                                                 // Vector for base tags
    std::string m_Str;                                                       // Container for readind file in

    XML_output *m_pOut;

    void nextTag(std::string &sTok, size_t &nCurPos, bool &fTagBegin);       // Find next tag (with the form <???>)
    void findTag(const std::string sName, size_t &nCurPos, bool fTagBegin);  // Find tag with name pName
    bool getContents(size_t nBegin, std::string &sCont);                     // Get contents between tag's beginning and end (not another tag)
    void readData(const char *FileName);                                     // Reading from the file
    void parseXml(std::vector <std::string> &Address);                       // Get tags' stucture and their contents to container
};

#endif // READXML_H

//***************************************************************************************************************

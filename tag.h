/**
  *************************************************************************************************************************
  * @file    tag.h
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    23-November-2018
  * @brief   The simple xml file's Tag implementation for parsing into
  *          In addition to the name and interger value can contain another tags to keep structure of enclosure of the xml
  **************************************************************************************************************************
*/

#ifndef TAG_H
#define TAG_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Tag;

typedef std::vector < std::shared_ptr <Tag> > VectorTagShared;
typedef VectorTagShared::iterator VectorTagSharedIter;

class TagAbsentExc {};                                          // Class for throwing search error exception

class Tag
{
public:
    Tag();
    Tag(std::string sName);
    ~Tag();

    std::string getName() const;
    void addTag(std::shared_ptr <Tag> shTag);                   // Add internal tag into current tag
    Tag getTag(size_t &nCurPos, std::string sName) const;       // Return tag with the name sName
    Tag getTag(std::string sName) const;
    VectorTagShared getInternalTags() const;
    void setValue(std::string sVal);
    uint32_t getValue() const;

private:
    std::string m_sName;                                        // Tag's name
    VectorTagShared m_tagVc;                                    // Vector for the included tags
    uint32_t m_nVal;

    void strToInt(std::string sVal);                            // Private member function for convertins value from string to int
};

#endif // TAG_H

//*******************************************************************************************************************************

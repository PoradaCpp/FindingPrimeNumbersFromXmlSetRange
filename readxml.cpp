/**
  *************************************************************************************************************************
  * @file    readxml.cpp
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

#include <stack>
#include <fstream>
#include <algorithm>

#include "readxml.h"
#include "xml_output.hpp"

/**
 * @brief Class ReadXml constructor
 * @param pFileName Name of the file to read
 * @param Address Address of target tags
 */
ReadXml::ReadXml(const char *pFileName, std::vector <std::string> Address): m_pOut(nullptr)
{
    readData(pFileName);
    parseXml(Address);
    m_Str.clear();
    m_Str.shrink_to_fit();
}

/**
 * @brief Class ReadXml destructor
 */
ReadXml::~ReadXml()
{
    if(m_pOut)
    {
        delete m_pOut;
    }
}

/**
 * @brief Read xml file
 * @param pFileName Name of the file to read
 * @return None
 */
void ReadXml::readData(const char *FileName)
{
    std::ifstream fin(FileName);
    size_t nFileSize;

    if(!fin)
    {
        std::cerr << "File opening error!\n";
        exit(1);
    }

    fin.seekg(0, std::ios::end);
    nFileSize = fin.tellg();

    m_Str.resize(nFileSize);
    fin.seekg(0);
    fin.read(&m_Str[0], nFileSize);
    fin.close();
}

/**
 * @brief Find next tag (with the form <???> or </???>) in the string with the xml file's contents
 * @param sTok Name of the tag which has been finded
 * @param nCurPos Current position of searching
 * @param fTagBegin Flag which shows if has been finded beginning (true) or end of the tag (false)
 * @return None
 */
void ReadXml::nextTag(std::string &sTok, size_t &nCurPos, bool &fTagBegin)
{
    size_t nTokBeg, nTokEnd, nTagEnd;

    nTokBeg = m_Str.find('<', nCurPos);
    nTokEnd = m_Str.find('>', nTokBeg);

    if(std::string::npos == nTokBeg || std::string::npos == nTokEnd)
    {
        nCurPos = std::string::npos;
        return;
    }

    nTagEnd = m_Str.find('/', nTokBeg);
    if(nTokEnd <  nTagEnd || std::string::npos == nTagEnd)
    {
        fTagBegin = true;
    }
    else
    {
        fTagBegin = false;
    }

    nCurPos = nTokEnd;
    nTokBeg = m_Str.find_first_not_of(m_pDelim, nTokBeg);
    nTokEnd = m_Str.find_last_not_of(m_pDelim, nTokEnd);

    sTok = m_Str.substr(nTokBeg, nTokEnd - nTokBeg + 1);
}

/**
 * @brief Find the tag with the name pName in the string with the xml file's contents
 * @param sName Name of the tag which need to find
 * @param nCurPos Current position of searching
 * @param fTagBegin Flag which set if need to find beginning (true) or end of the tag (false)
 * @return None
 */
void ReadXml::findTag(const std::string sName, size_t &nCurPos, bool fTagBegin)
{
    if(std::string::npos == nCurPos)
    {
        return;
    }

    std::string str;
    bool fTagState(!fTagBegin);

    while((sName != str || fTagState != fTagBegin) && std::string::npos != nCurPos)
    {
        nextTag(str, nCurPos, fTagState);
    }
}

/**
 * @brief Get contents between tag's beginning and end (not another tag) from the string with the xml file's contents
 * @param nBegin Position function need to start searching from
 * @param sCont Contents in string mapping
 * @return Flag whether the contents exists in current tag (true) or not (false)
 */
bool ReadXml::getContents(size_t nBegin, std::string &sCont)
{

    size_t nTokBeg, nTokEnd;

    nTokBeg = nBegin + 1;
    nTokEnd = m_Str.find('<', nTokBeg);

    if(std::string::npos == nTokEnd || nTokEnd == nTokBeg)
    {
        return false;
    }

    nTokBeg = m_Str.find_first_not_of(m_pDelim, nTokBeg);
    nTokEnd = m_Str.find_last_not_of(m_pDelim, nTokEnd);

    if(nTokEnd >= nTokBeg)
    {
        sCont = m_Str.substr(nTokBeg, nTokEnd - nTokBeg + 1);
        return true;
    }

    return false;
}

/**
 * @brief Get tags' stucture and their contents to container
 * @param Address Address of target tags
 * @return None
 */
void ReadXml::parseXml(std::vector<std::string> &Address)
{
    std::string str;
    size_t nCurPos(0);
    bool fTagBegin(true);
    std::stack < std::shared_ptr <Tag> > pTagStack;
    std::shared_ptr <Tag> tagPtr;

    if(Address.size())
    {
        for(size_t i = 0, p = Address.size(); i < p; ++i)
        {
            findTag(Address[i], nCurPos, true);                         // Go to the target address, if it has been set
        }
    }
    else
    {
        nextTag(str, nCurPos, fTagBegin);                               // If the address has not been set, write to Addres string
        Address.push_back(str);                                         // the name of the first tag in file
        str.clear();
    }

    if(std::string::npos == nCurPos)                                    // Return if address has been set but not found
    {
        return;
    }

    // While address of the beginning of the target tag or the file not be caught (again) and it will be the end of the tag
    while((Address.back() != str || false != fTagBegin) && std::string::npos != nCurPos)
    {
        nextTag(str, nCurPos, fTagBegin);

        if(fTagBegin)                                                 /// If it is the beginnins of the tag
        {
            if(pTagStack.empty())                                        // If it the beginnihg of the branch of the tags' tree
            {
                m_tagVc.emplace_back(std::make_shared <Tag> (str));      // Create tag in the base tags container
                pTagStack.push(m_tagVc.back());                          // Push it to stacks
            }
            else                                                         // Else tag is not the base, it includs in base tag
            {
                tagPtr = std::make_shared <Tag> (str);                   // Create it,
                pTagStack.top()->addTag(tagPtr);                         //   place into the last tag
                pTagStack.push(tagPtr);                                  //   and push it to stack
            }

            if(getContents(nCurPos, str))                                // If we have some contents in the tag,
            {
                pTagStack.top()->setValue(str);                          //   add it to the tag
            }
        }
        else if(pTagStack.size())                                      /// Else if it is the end of the tag, and we have something in the stack
        {
            pTagStack.pop();                                             //   pop it out from the stack
        }
    }
}

/**
 * @brief Searching tag with the name sName from the position nCurPos to the end of vector of tags
 * @param nCurPos Position to search from. Could be used in cycle
 * @param sName Name of the tag which need to find
 * @return Copy of the finded tag. If such tag is not exist, return tag with the name "EMPTY_TAG"
 */
Tag ReadXml::getTag(size_t &nCurPos, std::string sName) const
{
    for(size_t p = m_tagVc.size(); nCurPos < p; ++nCurPos)
    {
        if(m_tagVc[nCurPos]->getName() == sName)
        {
            return *(m_tagVc[nCurPos++].get());
        }
    }

    return Tag("EMPTY_TAG");
}

/**
 * @brief Get tag's contents
 * @param Address Address of target tag
 * @return Interger value of the contents
 */
uint32_t ReadXml::findData(std::vector<std::string> Address) const
{
    std::shared_ptr <Tag> tagPtr;

    auto Iter = std::find_if(m_tagVc.begin(), m_tagVc.end(), [ &Address ] (std::shared_ptr <Tag> sh) // Go to the target address base tag
    {
        return Address[0] == sh->getName();
    });

    if(Iter == m_tagVc.end())                                                                 // If address not exist,
    {
        throw AddressNotExist();                                                              //   throwing the exception
    }

    tagPtr = *Iter;

    for(size_t i = 1, p = Address.size(); i < p; ++i)                                         // Going to the address tag
    {
        try
        {
            tagPtr = std::make_shared <Tag> (tagPtr->getTag(Address[i]));                     // Try to find tag with the required name
        }
        catch(const TagAbsentExc&)
        {
            std::cerr << "Object " << Address[i] << " was not found!\n";
            return 0;
        }
    }

    return tagPtr->getValue();                                                                // Returns value
}

/**
 * @brief Set specific derived class from the abstract class XmlOutput to set the output method behaviour
 * @param pOut Pointer to the abstract class XmlOutput, which points to the specific derived class
 * @return None
 */
void ReadXml::setOutput(XML_output *pOut)
{
    if(m_pOut)
    {
        delete m_pOut;
    }

    m_pOut = pOut;
}

/**
 * @brief Method to processing input data and get them to the output class derived from the abstract class XmlOutput
 *        by the way which set in it
 * @param None
 * @return None
 */
void ReadXml::output() const
{
    m_pOut->output(*this);
}

//*******************************************************************************************************

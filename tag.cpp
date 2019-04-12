/**
  *************************************************************************************************************************
  * @file    tag.cpp
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    23-November-2018
  * @brief   The simple xml file's Tag implementation for parsing into
  *          In addition to the name and interger value can contain another tags to keep structure of enclosure of the xml
  **************************************************************************************************************************
*/

#include "tag.h"

/**
 * @brief Class Tag constructor
 * @param None
 */
Tag::Tag(): m_sName(" "), m_nVal(0) {}

/**
 * @brief Class Tag constructor
 * @param sName name of the tag
 */
Tag::Tag(std::string sName): m_sName(sName), m_nVal(0) {}

/**
 * @brief Class Tag destructor
 */
Tag::~Tag() {}

/**
 * @brief Tag name getter
 * @param None
 * @return Name of the tag
 */
std::string Tag::getName() const
{
    return m_sName;
}

/**
 * @brief Add internal tag into current tag
 * @param shTag shared_ptr to tag which need to add
 * @return None
 */
void Tag::addTag(std::shared_ptr<Tag> shTag)
{
    m_tagVc.push_back(shTag);
}

/**
 * @brief Find tag with the name sName among internal tag from the nCurPos to the end of vector of tags
 * @param nCurPos Position to search from. Could be used in cycle
 * @param sName Name of the tag for searching
 * @return m_tagVc[i] shared_ptr to tag with the name sName
 */
Tag Tag::getTag(size_t &nCurPos, std::string sName) const
{
    for(size_t p = m_tagVc.size(); nCurPos < p; ++nCurPos)
    {
        if(m_tagVc[nCurPos]->m_sName == sName)
            return *(m_tagVc[nCurPos++].get());
    }

    return Tag("EMPTY_TAG");
}

/**
 * @brief Find tag with the name sName among internal tag
 * @param sName Name of the tag for searching
 * @return m_tagVc[i] shared_ptr to tag with the name sName
 */
Tag Tag::getTag(std::string sName) const
{

    for(size_t i = 0, p = m_tagVc.size(); i < p; ++i)
    {
        if(m_tagVc[i]->m_sName == sName)
            return *(m_tagVc[i].get());
    }

    return Tag("EMPTY_TAG");
}

/**
 * @brief Returns copy of the vector of the internal tags
 * @param None
 * @return Vector of shared_ptr to tag
 */
VectorTagShared Tag::getInternalTags() const
{
    return m_tagVc;
}

/**
 * @brief Set internal value for the current tag
 * @param sVal Value from xml, in current project it's interger value in string mapping
 * @return None
 */
void Tag::setValue(std::string sVal)
{
    strToInt(sVal);
}

/**
 * @brief Convert interger value in string mapping to digits mapping
 * @param sVal Interger value from xml in string mapping
 * @return None
 */
void Tag::strToInt(std::string sVal)
{
    for(int i = sVal.size() - 1, j = 1; i >= 0; --i, j *= 10)
        m_nVal += (sVal[i] - 48) * j;
}

/**
 * @brief Return value from the current tag
 * @param None
 * @return m_nVal The value contains in the current tag
 */
uint32_t Tag::getValue() const
{
    return m_nVal;
}

//*******************************************************************************************************

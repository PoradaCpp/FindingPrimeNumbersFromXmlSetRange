/**
  ******************************************************************************************************************************
  * @file    intervalsoutput.cpp
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    18-December-2018
  * @brief   Derived class from the abstract class Xml_output.hpp which implements getting numeric intervals from the parsed xml file
  ******************************************************************************************************************************
*/

#include <algorithm>

#include "intervalsoutput.h"

/**
 * @brief Class IntervalsOutput constructor
 * @param IntVc Container to fill intervals in
 */
IntervalsOutput::IntervalsOutput(std::vector<Interval> *pIntVc): XML_output(), m_pIntVc(pIntVc) {}

/**
 * @brief Class IntervalsOutput destructor
 */
IntervalsOutput::~IntervalsOutput() {}

/**
 * @brief Implementation of the abstract function to get intervals from tags
 * @param IntVc Container to fill intervals in
 * @return None
 */
void IntervalsOutput::output(const ReadXml &ParserXml)
{
    size_t nCurPos(0);

    for(Tag tag = ParserXml.getTag(nCurPos, "intervals"); tag.getName() != "EMPTY_TAG"; tag = ParserXml.getTag(nCurPos, "intervals"))
    {
        getIntervals(tag.getInternalTags());
    }
}

/**
 * @brief Function to get intervals from tags, arrange them (sort and merge, if them intersect)
 * @param TagShVc Container of tags which contains intervals data
 * @return None
 */
void IntervalsOutput::getIntervals(VectorTagShared TagShVc)
{
    uint32_t nLowIntervalSide(0), nHighIntervalSide(0);
    bool fAdd(true);

    for(size_t i = 0, p = TagShVc.size(); i < p; ++i)
    {
        nLowIntervalSide = (TagShVc[i]->getTag("low")).getValue();      //
        nHighIntervalSide = (TagShVc[i]->getTag("high")).getValue();    // Get values

        if(nLowIntervalSide > nHighIntervalSide)                          // If Low and High are mixed, swap them
        {
            uint32_t nTmp = nLowIntervalSide;
            nLowIntervalSide = nHighIntervalSide;
            nHighIntervalSide = nTmp;
        }

        for(size_t j = 0, q = m_pIntVc->size(); j < q; ++j)                // If intervals intersect, merge them
        {
            if(nLowIntervalSide < (*m_pIntVc)[j].m_nLowIntervalSide)
            {
                if(nHighIntervalSide > (*m_pIntVc)[j].m_nHighIntervalSide)
                {
                    (*m_pIntVc)[j].m_nLowIntervalSide = nLowIntervalSide;
                    (*m_pIntVc)[j].m_nHighIntervalSide = nHighIntervalSide;
                    fAdd = false;
                }
                else if(nHighIntervalSide > (*m_pIntVc)[j].m_nLowIntervalSide)
                {
                    (*m_pIntVc)[j].m_nLowIntervalSide = nLowIntervalSide;
                    fAdd = false;
                }
            }
            else if(nLowIntervalSide <= (*m_pIntVc)[j].m_nHighIntervalSide)
            {
                if(nHighIntervalSide > (*m_pIntVc)[j].m_nHighIntervalSide)
                {
                    (*m_pIntVc)[j].m_nHighIntervalSide = nHighIntervalSide;
                }
                fAdd = false;
            }
        }

        if(fAdd)
        {
            m_pIntVc->emplace_back(nLowIntervalSide, nHighIntervalSide);    // Result write into vector
        }
        else
        {
            fAdd = true;
        }
    }
    std::sort(m_pIntVc->begin(), m_pIntVc->end());                           // Sorting
}

//*******************************************************************************************************


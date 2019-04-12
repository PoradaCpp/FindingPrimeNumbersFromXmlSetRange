/**
  ******************************************************************************************************************************
  * @file    intervalsoutput.h
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    18-December-2018
  * @brief   Derived class from the abstract class Xml_output which implements getting numeric intervals from the parsed xml file
  ******************************************************************************************************************************
*/

#ifndef INTERVALSOUTPUT_H
#define INTERVALSOUTPUT_H

#include <vector>
#include <memory>

#include "interval.hpp"
#include "xml_output.hpp"

class IntervalsOutput: public XML_output
{
public:
    IntervalsOutput(std::vector <Interval> *pIntVc);
    ~IntervalsOutput() override;

    void output(const ReadXml &ParserXml) override;

private:
    std::vector <Interval> *m_pIntVc;

    void getIntervals(VectorTagShared TagShVc);
};

#endif // INTERVALSOUTPUT_H

//*****************************************************************************************

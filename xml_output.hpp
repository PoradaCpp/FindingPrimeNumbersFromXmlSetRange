/**
  *************************************************************************************************************************
  * @file    xml_output.hpp
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    18-December-2018
  * @brief   The abstract class to get result of parsing xml file
  ***************************************************************************************************************************
*/

#ifndef XML_OUTPUT_HPP
#define XML_OUTPUT_HPP

#include "readxml.h"

class XML_output
{
public:

    XML_output() {}
    virtual ~XML_output() {}

    virtual void output(const ReadXml &ParserXml) = 0;
};

#endif // XML_OUTPUT_HPP

//**************************************************************************************************************************

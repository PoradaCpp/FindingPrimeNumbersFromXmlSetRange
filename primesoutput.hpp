/**
  *************************************************************************************************************************
  * @file    PrimesOutput.hpp
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    23-December-2018
  * @brief   The abstract class to output result of searching prime numbers
  **************************************************************************************************************************
*/

#ifndef PRIMESOUTPUT_HPP
#define PRIMESOUTPUT_HPP

#include <vector>

#include "primenumbersvector.h"

class PrimesOutput
{
public:

    PrimesOutput() {}
    virtual ~PrimesOutput() {}

    virtual void output(PrimeNumbersVector *pPrimeNumVc) = 0;
};

#endif // PRIMESOUTPUT_HPP


//**************************************************************************************************************************

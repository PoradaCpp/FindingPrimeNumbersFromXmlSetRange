/**
  ******************************************************************************************************************************
  * @file    primesconsoleoutput.h
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    25-December-2018
  * @brief   Derived class from the abstract class PrimesOutput which implements printing to console prime numbers
  *          from FindPrimes object
  ******************************************************************************************************************************
*/

#ifndef PRIMESCONSOLEOUTPUT_H
#define PRIMESCONSOLEOUTPUT_H

#include "primesoutput.hpp"

class PrimesConsoleOutput: public PrimesOutput
{
public:
    PrimesConsoleOutput();
    ~PrimesConsoleOutput() override;

    void output(PrimeNumbersVector *pPrimeNumVc) override;
};

#endif // PRIMESCONSOLEOUTPUT_H

//*****************************************************************************************************************************

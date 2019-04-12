/**
  ******************************************************************************************************************************
  * @file    primesfileoutput.h
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    25-December-2018
  * @brief   Derived class from the abstract class PrimesOutput which implements printing to file prime numbers
  *          from FindPrimes object
  ******************************************************************************************************************************
*/

#ifndef PRIMESFILEOUTPUT_H
#define PRIMESFILEOUTPUT_H

#include "primesoutput.hpp"

class PrimesFileOutput: public PrimesOutput
{
public:
    PrimesFileOutput(const char *pFileName);
    virtual ~PrimesFileOutput() override;

    void output(PrimeNumbersVector *pPrimeNumVc) override;

private:
    const char *m_pFileName;
};

#endif // PRIMESFILEOUTPUT_H

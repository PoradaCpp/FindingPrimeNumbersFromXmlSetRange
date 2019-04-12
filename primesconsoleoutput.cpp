/**
  ******************************************************************************************************************************
  * @file    primesconsoleoutput.cpp
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    25-December-2018
  * @brief   Derived class from the abstract class PrimesOutput which implements printing to console prime numbers
  *          from FindPrimes object
  ******************************************************************************************************************************
*/

#include "primesconsoleoutput.h"

#include <iostream>

/**
 * @brief Class PrimesConsoleOutput constructor
 * @param None
 */
PrimesConsoleOutput::PrimesConsoleOutput(): PrimesOutput() {}

/**
 * @brief Class IntervalsOutput destructor
 */
PrimesConsoleOutput::~PrimesConsoleOutput() {}

/**
 * @brief Implementation of the abstract function to output prime numbers (print to console) from PrimeNumbersVector
 * @param pPrimeNumVc Container to prime numbers from
 * @return None
 */
void PrimesConsoleOutput::output(PrimeNumbersVector *pPrimeNumVc)
{
    for(uint32_t i = 0, p = pPrimeNumVc->size(), nNum = 0; i < p; ++i)
    {
        nNum = pPrimeNumVc->at(i);
        if(nNum)
        {
            std::cout << nNum << ' ';
        }
    }
}

//*****************************************************************************************************************************

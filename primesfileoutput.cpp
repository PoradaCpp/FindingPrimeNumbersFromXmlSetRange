/**
  ******************************************************************************************************************************
  * @file    primesfileoutput.cpp
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    25-December-2018
  * @brief   Derived class from the abstract class PrimesOutput which implements printing to file prime numbers
  *          from FindPrimes object
  ******************************************************************************************************************************
*/

#include "primesfileoutput.h"

#include <iostream>
#include <fstream>

/**
 * @brief Class PrimesFileOutput constructor
 * @param pFileName Name of the file to write in
 */
PrimesFileOutput::PrimesFileOutput(const char* pFileName): PrimesOutput(), m_pFileName(pFileName) {}

/**
 * @brief Class IntervalsOutput destructor
 */
PrimesFileOutput::~PrimesFileOutput() {}

/**
 * @brief Implementation of the abstract function to output prime numbers (print to file) from PrimeNumbersVector
 * @param pPrimeNumVc Container to prime numbers from
 * @return None
 */
void PrimesFileOutput::output(PrimeNumbersVector *pPrimeNumVc)
{
    std::ofstream out(m_pFileName);

    if(!out)
    {
        std::cerr << "File opening error!\n";
        exit(1);
    }

    out << "<root>\n<primes> ";

    for(uint32_t i = 0, p = pPrimeNumVc->size(), nNum = 0; i < p; ++i)
    {
        nNum = pPrimeNumVc->at(i);
        if(nNum)
        {
            out << nNum << ' ';
        }
    }

    out << "</primes>\n</root>";
    out.close();
}

//*****************************************************************************************************************************

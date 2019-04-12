/**
  *************************************************************************************************************************
  * @file    primenumfunc.cpp
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    23-November-2018
  * @brief   Class-functor to be given into particular thread (for multy-threads prime numbers searching)
  **************************************************************************************************************************
*/

#include <cmath>

#include "primenumfunc.h"
#include "findprimes.h"

/**
 * @brief Class PrimeNumFunc constructor
 * @param pfVc Bool vector pointer to save result in it
 * @param pPrimesVec Initial primes for searching another primes
 * @param nSpokesVec Spokes of Wheel Factorisation container (only for current thread!)
 * @param pIntVec Intervals vector pointer
 * @param nPrimor Primorial of Wheel Factorisation
 * @param nBegPrimesNum Number of initial primes of Wheel Factorisation
 */
PrimeNumFunc::PrimeNumFunc(std::vector <bool> *pfVc, std::vector<uint32_t> *pPrimesVec, std::vector<uint32_t> &&nSpokesVec,
                               std::vector<Interval> *pIntVec, uint32_t nPrimor, uint32_t nBegPrimesNum):
    m_pfVc(pfVc),
    m_pPrimesVec(pPrimesVec),
    m_nSpokesVec(std::move(nSpokesVec)),
    m_pIntVec(pIntVec),
    m_nPrimor(nPrimor),
    m_nNumOfSpokes(m_nSpokesVec.size()),                         // Number of spokes of Wheel Factorisation
    m_nBegPrimesNum(nBegPrimesNum) {}

/**
 * @brief Class PrimeNumFunc destructor
 */
PrimeNumFunc::~PrimeNumFunc() {}

/**
 * @brief Function for finding prime numbers by the Eratosthenes Sieve method with the wheel factorisation
 * @param None
 * @return None
 */
void PrimeNumFunc::operator () ()
{
    uint32_t nBegin, nVal, nPreDiv, nHigh, nLow;

    nBegin = sqrtf((m_pIntVec->back()).m_nHighIntervalSide);            // Numbers less than sqrtf(High) are already finded

    for(uint32_t m = 0, q = m_pIntVec->size(); m < q; ++m)              // For each interval
    {
        nHigh = (*m_pIntVec)[m].m_nHighIntervalSide;                    //
        nLow = (*m_pIntVec)[m].m_nLowIntervalSide;                      // Get limits

        if(nHigh < nBegin)
        {
            continue;                                                   // If interval is in initial primes, go to another inteval
        }
        if(nLow > nBegin)                                               // Choose position to start searcing from
        {
            nBegin = nLow;
        }

        for(uint32_t i = m_nBegPrimesNum, p = m_pPrimesVec->size(); i < p; ++i)  // For each initial prime
        {
            nVal = (*m_pPrimesVec)[i];
            nPreDiv = 1 + nBegin / nVal;                                // Count value to start

            for(uint32_t k = 0; k < m_nNumOfSpokes; ++k)                // For all spokes in current thread
            {
                for(uint32_t j = nVal * nPreDiv; j < nHigh; j += nVal)  // Count last value < nBegin, and increment it with the step nVal
                {
                    if(!((j - m_nSpokesVec[k]) % m_nPrimor))            // If the value belongs to m_nPrimor * x + m_nSpokesVc[i] series
                    {
                        for(uint32_t r = nVal * m_nPrimor; j < nHigh; j += r)  // change step to optimal
                        {
                            (*m_pfVc)[j] = true;
                        }
                        break;
                    }
                }
            }
        }
    }
}

//***********************************************************************************************************************

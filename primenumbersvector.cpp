/**
  ******************************************************************************************************************************
  * @file    primenumbersvector.cpp
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    25-December-2018
  * @brief   Сlass-adapter for bool vector to simplify getting prime numbers from it
  ******************************************************************************************************************************
*/

#include <algorithm>
#include <numeric>

#include "primenumbersvector.h"
#include "interval.hpp"

/**
 * @brief Class PrimeNumbersVector constructor
 * @param p_fVector     Pointer to vector with result in it
 * @param pIntVector    Pointer to vector of intervals in which prime numbers has been searched
 * @param pPrimesVector Pointer to vector of initial prime numbers
 * @param pSpokesVector Pointer to vector of spokes of Wheel Factorisation container
 * @param nPrimor       Primorial of Wheel Factorisation
 * @param nBegPrimesNum Number of spokes of Wheel Factorisation
 */
PrimeNumbersVector::PrimeNumbersVector(std::vector <bool> *p_fVector, std::vector <Interval> *pIntVector,
                                       std::vector <uint32_t> *pPrimesVector, std::vector <uint32_t> *pSpokesVector,
                                       uint32_t &nPrimor, uint32_t &nBegPrimesNum):
    m_pfVector(p_fVector),
    m_pIntVector(pIntVector),
    m_pPrimesVector(pPrimesVector),
    m_pSpokesVector(pSpokesVector),
    m_nPrimor(nPrimor),
    m_nNumOfSpokes(m_pSpokesVector->size()),
    m_nBegPrimesNum(nBegPrimesNum),
    m_nMax(m_pIntVector->back().m_nHighIntervalSide)
{
    countEffectiveSize();
}

/**
 * @brief Class PrimeNumbersVector destructor
 */
PrimeNumbersVector::~PrimeNumbersVector() {}

/**
 * @brief Counts effective size of the bool vector
 * @param None
 * @return None
 */
void PrimeNumbersVector::countEffectiveSize()
{
    // Counting the part of common size which contains the Wheel Factorization Series
    float fitSizeCoeff = 1 - std::accumulate(m_pPrimesVector->begin(), m_pPrimesVector->begin() + m_nBegPrimesNum, 0.0,
    [] (float fitResult, uint32_t nPrime)
    {
        return fitResult = fitResult + 1.0/nPrime - fitResult/nPrime;
    });

    m_nSize = m_nMax * fitSizeCoeff + 1;
}

/**
 * @brief Retuns the effective size of the bool vector
 * @param None
 * @return m_nSize The effective size of the bool vector
 */
size_t PrimeNumbersVector::size() const
{
    return m_nSize;
}

/**
 * @brief Returns the value of the element at specified location pos, with bounds checking
 * @param nPos Position of the element to return
 * @return nCurNum The value of the element
 * @exceptions OutOfRange if !(nPos < m_nSize()).
 */
uint32_t PrimeNumbersVector::at(size_t nPos) const
{
    uint32_t nCurNum(0);

    if(nPos < m_nSize)
    {
        if(nPos < m_pPrimesVector->size())                                     // If nPos belongs to initial primes
        {
            nCurNum = (*m_pPrimesVector)[nPos];                                //   get the value from vector of initial primes
        }
        else
        {
            uint32_t nCurSpoke = nPos % m_nNumOfSpokes;                        // Else count nVal's spoke number,
            uint32_t nCurIndex = nPos / m_nNumOfSpokes;                        //  the value of index,
            nCurNum = nCurIndex * m_nPrimor + (*m_pSpokesVector)[nCurSpoke];   //  and result: the value, which corresponds to nPos

            if(true == (*m_pfVector)[nCurNum])                                 // If nCurNum is not prime number
            {
                nCurNum = 0;
            }
        }

        //Check whether nCurNum belongs to any interval
        bool fBelongIntervals = std::any_of(m_pIntVector->begin(), m_pIntVector->end(), [ nCurNum ] (Interval Int)
        {
             return ((nCurNum >= Int.m_nLowIntervalSide) && (nCurNum <= Int.m_nHighIntervalSide));
        });

        if(!fBelongIntervals)
        {
            nCurNum = 0;
        }
    }
    else
    {
        throw OutOfRange();
    }

    return nCurNum;
}

//*******************************************************************************************************

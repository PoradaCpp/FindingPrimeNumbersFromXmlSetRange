/**
  ******************************************************************************************************************************
  * @file    primenumbersvector.h
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    25-December-2018
  * @brief   Сlass-adapter for bool vector to simplify getting prime numbers from it
  ******************************************************************************************************************************
*/

#ifndef VECTORPRIMES_H
#define VECTORPRIMES_H

#include <vector>
#include <iostream>


class Interval;
class OutOfRange {};                            // Class for throwing exception when given index to PrimeNumbersVector is out of range

class PrimeNumbersVector
{
public:
    PrimeNumbersVector(std::vector <bool> *p_fVector, std::vector <Interval> *pIntVector, std::vector <uint32_t> *pPrimesVector,
                       std::vector <uint32_t> *pSpokesVector, uint32_t &nPrimor, uint32_t &nBegPrimesNum);
    ~PrimeNumbersVector();

    size_t size() const;
    uint32_t at(size_t nPos) const;

private:
    std::vector <bool> *m_pfVector;             // Pointer to vector with result in it
    std::vector <Interval> *m_pIntVector;       // Intervals in which prime numbers has been searched
    std::vector <uint32_t> *m_pPrimesVector;    // Initial prime numbers
    std::vector <uint32_t> *m_pSpokesVector;    // Spokes of Wheel Factorisation container
    uint32_t m_nPrimor;                         // Primorial of Wheel Factorisation
    uint32_t m_nNumOfSpokes;                    // Number of spokes of Wheel Factorisation
    uint32_t m_nBegPrimesNum;                   // Number of initial primes of Wheel Factorisation
    uint32_t m_nMax;                            // Max number of all intervals
    size_t m_nSize;                             // Effective size of the bool vector

    void countEffectiveSize();
};

#endif // VECTORPRIMES_H

//*****************************************************************************************

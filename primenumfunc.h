/**
  *************************************************************************************************************************
  * @file    primenumfunc.h
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    23-November-2018
  * @brief   Class-functor to be given into particular thread (for multy-threads prime numbers searching)
  **************************************************************************************************************************
*/


#ifndef PRIMENUMFUNC_H
#define PRIMENUMFUNC_H

#include <iostream>
#include <vector>

#include "interval.hpp"

class PrimeNumFunc
{
public:
    PrimeNumFunc(std::vector <bool> *pfVc, std::vector <uint32_t> *pPrimesVec, std::vector <uint32_t> &&nSpokesVec, std::vector <Interval> *pIntVec, uint32_t nPrimor, uint32_t nBegPrimesNum);

    ~PrimeNumFunc();

    void operator () ();

private:
    std::vector <bool> *m_pfVc;                 // Bool vector pointer to save result in it
    std::vector <uint32_t> *m_pPrimesVec;       // Initial primes for searching another primes
    std::vector <uint32_t> m_nSpokesVec;        // Spokes of Wheel Factorisation container (only for current thread!)
    std::vector <Interval> *m_pIntVec;          // Intervals vector pointer

    uint32_t m_nPrimor;                         // Primorial of Wheel Factorisation
    uint32_t m_nNumOfSpokes;                    // Number of spokes of Wheel Factorisation
    uint32_t m_nBegPrimesNum;                   // Number of initial primes of Wheel Factorisation
};

#endif // PRIMENUMFUNC_H

//******************************************************************************************************************

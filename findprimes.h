/**
  *************************************************************************************************************************
  * @file    findprimes.h
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    23-November-2018
  * @brief   Class for searching prime numbers in given intervals
  **************************************************************************************************************************
*/

#ifndef FINDPRIMES_H
#define FINDPRIMES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

#include "primenumfunc.h"
#include "interval.hpp"
#include "primenumbersvector.h"
#include "primesoutput.hpp"

class FindPrimes
{
public:
    FindPrimes(std::vector <Interval> *pIntVc);
    ~FindPrimes();

    void setOutput(PrimesOutput *pOutput);
    void output() const;

    PrimeNumbersVector *m_pPrimeNumVector;                  // Adapter for the bool vector to output the result of searching

private:
    std::vector <bool> m_fVc;                               // Bool vector to save result in it
    std::vector <uint32_t> m_nPrimesVc;                     // Initial primes for searching another primes
    std::vector <uint32_t> m_nSpokesVc;                     // Spokes of Wheel Factorisation container
    std::vector <PrimeNumFunc> m_PNSearchVc;                // Functor container for threads
    std::vector <std::thread> m_threadsVc;                  // Threads vector
    std::vector <Interval> *m_pIntVc;                       // Vector of intervals for searching in

    PrimesOutput *m_pOutput;                                // Abstract class pointer to define the output method

    uint32_t m_nMax;                                        // Max number of all intervals
    uint32_t m_nMin;                                        // Min number of all intervals
    uint32_t m_nBegPrimesNum;                               // Number of initial primes of Wheel Factorisation
    uint32_t m_nNumOfThreads;                               // Number of threads
    uint32_t m_nNumOfRanges;                                // Number of intervals for searching
    uint32_t m_nPrimor;                                     // Primorial of Wheel Factorisation
    uint32_t m_nNumOfSpokes;                                // Number of spokes of Wheel Factorisation
    uint32_t m_nKernels;                                    // Number of kernels (from std::thread::hardware_concurrency())
    uint32_t m_nMaxBegPrime;                                // Max of initial primes

    void inputDataProcessing();                             // Count number of initial prime numbers, determine how many threads to make for intervals
    void findPrimesEnum();                                  // Finding initial primes
    void eratosthenesSieve(uint32_t nMin);                  // Eratosthenes Sieve specified function for current application
    void countPrimorial();
    void findWheelSpokes();                                 // Finding Spokes of Wheel Factorisation
    void multyThreadPrimesSearching();                      // Filling functor vector and threads vector. Starting threads
    std::vector<uint32_t> getSpokes(uint32_t nThreadNum);   // Returns part of spokes (as vector) for each thresd
};

#endif // FINDPRIMES_H

//*********************************************************************************************************

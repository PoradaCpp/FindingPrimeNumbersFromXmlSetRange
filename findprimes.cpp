/**
  *************************************************************************************************************************
  * @file    findprimes.cpp
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    23-November-2018
  * @brief   Class for searching prime numbers in given intervals
  **************************************************************************************************************************
*/


#include <cmath>

#include "findprimes.h"

/**
 * @brief Class FindPrimes constructor
 * @param pIntVec Intervals vector pointer
 */
FindPrimes::FindPrimes(std::vector<Interval> *pIntVc):
   m_pPrimeNumVector(nullptr),
    m_pIntVc(pIntVc),
    m_pOutput(nullptr),
    m_nPrimor(1)                                 // Init primorial with 1 to use in multiplication operations

{
    inputDataProcessing();                       // Count number of initial prime numbers, determine how many threads to make for intervals
    findWheelSpokes();

    if(m_nPrimor)                                // If searching limits are bigger than initial prime numbers
    {
        m_nNumOfSpokes = m_nSpokesVc.size();
        multyThreadPrimesSearching();            //   find prime numbers
        m_pPrimeNumVector = new PrimeNumbersVector(&m_fVc, m_pIntVc, &m_nPrimesVc, &m_nSpokesVc, m_nPrimor, m_nBegPrimesNum);
    }
}

/**
 * @brief Class FindPrimes destructor
 */
FindPrimes::~FindPrimes()
{
    if(m_pPrimeNumVector)
    {
        delete m_pPrimeNumVector;
    }

    if(m_pOutput)
    {
        delete m_pOutput;
    }
}

/**
 * @brief Function to count number of initial prime numbers, determine how many threads to make for intervals
 * @param None
 * @return None
 */
void FindPrimes::inputDataProcessing()
{
    m_nNumOfRanges = m_pIntVc->size();
    if(!m_nNumOfRanges)
    {
        return;
    }

    m_nMin = m_pIntVc->front().m_nLowIntervalSide;        //
    m_nMax = m_pIntVc->back().m_nHighIntervalSide;        // Get limits

    m_nKernels = std::thread::hardware_concurrency();     // Get number of threads to work really parallel for current computer
    m_nNumOfThreads = 2 * m_nKernels;                     // Maximum number of threads for effective work
    if(m_nNumOfRanges < m_nNumOfThreads)
    {
        m_nNumOfThreads = m_nNumOfRanges;                 // Necessary number of threads for given ranges
    }

    if(m_nNumOfThreads > 0 && m_nNumOfThreads < 3)        //
    {                                                     //
        if(m_nMax < 100000)                               // Make decision how many initial primes we use for searching
        {                                                 //   depends on searching limits and intervals guantity
            m_nBegPrimesNum = 2;                          //
        }                                                 //
        else if(m_nMax < 1000000)                         //
        {                                                 //
            m_nBegPrimesNum = 3;                          //
        }                                                 //
        else                                              //
        {                                                 //
            m_nBegPrimesNum = 4;                          //
        }                                                 //
    }                                                     //
    else if(m_nNumOfThreads < 9)                          //
    {                                                     //
        if(m_nMax < 2000000)                              //
        {                                                 //
            m_nBegPrimesNum = 3;                          //
        }                                                 //
        else                                              //
        {                                                 //
            m_nBegPrimesNum = 4;                          //
        }                                                 //
    }                                                     //
    else if(m_nNumOfThreads < 49)                         //
    {                                                     //
        m_nBegPrimesNum = 4;                              //
    }                                                     //
    else
    {
        exit(1);                                          // If limits are wrong, close the program
    }
}

/**
 * @brief Function to find prime number by the method of simple search, most quick for small intervals
 * @param None
 * @return None
 */
void FindPrimes::findPrimesEnum()
{
    bool fPrime(true);                                           // Flag if the number is orime
    uint32_t nQuant = 1 + sqrtf(m_nMax);                         // Limit for searchind
    if(nQuant < m_nBegPrimesNum)
    {
        nQuant = m_nBegPrimesNum;                                // Processing situation for many intervals in small limit
    }

    for(uint32_t i  = 2, j = 0; j < nQuant && i < nQuant; ++i)   // For all numbers 2...limit
    {
        for(uint32_t k  = 0, m = 0, n = 1 + sqrtf(i); m < n && k < j; ++k)  // For each vector index 0...max
        {
            m = (j > 0 ? m_nPrimesVc[k] : 1);                    // If vector is not empty, get value from to m

            if(!(i % m))                                         // And check i % m,
            {
                fPrime = false;                                  //   if i % m == 0, i is not prime number,
                break;                                           //   so breack the loop
            }
        }
        if(fPrime)                                               // If we check i fo all prime numbers 2...sqrt(i),
        {                                                        //    i is the prime number,
            m_nPrimesVc.push_back(i);                            //    so write it to vector,
            ++j;                                                 //    increment prime numbers capasity variable
            if(j == m_nBegPrimesNum)
            {
                m_nMaxBegPrime = i;                              //    Save max prime number for Wheel Factorisation
            }
        }
        else
        {
            fPrime = true;
        }
    }
}

/**
 * @brief Function to find prime number by the method of Eratosthenes Sieve. Use it to find Wheel spokes
 * @param nMin Minimal value of spokes to find
 * @return None
 */
void FindPrimes::eratosthenesSieve(uint32_t nMin)
{
    for(uint32_t i = 2, p = nMin + 1; i < p; ++i)
    {
        if(!(m_fVc[i]))
        {
            for(uint32_t j = i * i; j < m_nPrimor; j += i)
            {
                m_fVc[j] = true;
            }
        }
    }
    for(uint32_t i = 2; i < m_nPrimor; ++i)
    {
        if(!(m_fVc[i]) && i > nMin)
        {
            m_nSpokesVc.push_back(i);
        }
    }
}

/**
 * @brief Function to count primorial
 * @param None
 * @return None
 */
void FindPrimes::countPrimorial()
{
    for(uint32_t i = 0; i < m_nBegPrimesNum; ++i)
    {
        m_nPrimor *= m_nPrimesVc[i];
    }
}

/**
 * @brief Function to collect several operations: find initial primes, count primorial, and finally find wheel spokes
 * @param None
 * @return None
 */
void FindPrimes::findWheelSpokes()
{
    findPrimesEnum();

    if(m_nMaxBegPrime >= m_nMax)
    {
        m_nPrimor = 0;
        return;
    }

    countPrimorial();
    m_fVc.resize(m_nPrimor, 0);

    m_nSpokesVc.push_back(1);
    eratosthenesSieve(m_nMaxBegPrime);

    m_fVc.assign(m_fVc.size(), false);

    if(m_nMax > m_nPrimor)
    {
        m_fVc.resize(m_nMax, false);
    }
}

/**
 * @brief Function to choose nesessary part of spokes for each thread and collect it to vector
 * @param nThreadNum Serial number of thread
 * @return nSpokesVc Vector with spokes
 */
std::vector <uint32_t> FindPrimes::getSpokes(uint32_t nThreadNum)
{
    std::vector <uint32_t> nSpokesVc;
    uint32_t nSpokesPerThread = m_nNumOfSpokes / m_nNumOfThreads;

    for(uint32_t i = nThreadNum * nSpokesPerThread, p = (nThreadNum + 1) * nSpokesPerThread; i < p; ++i)
    {
        nSpokesVc.push_back(m_nSpokesVc[i]);
    }

    return nSpokesVc;
}

/**
 * @brief Function to create PrimeNumFunc objects, create threads, start threads and wait for their end
 * @param None
 * @return None
 */
void FindPrimes::multyThreadPrimesSearching()
{
    for(uint32_t i = 0; i < m_nNumOfThreads; ++i)
    {
        m_PNSearchVc.emplace_back(&m_fVc, &m_nPrimesVc, getSpokes(i), m_pIntVc, m_nPrimor, m_nBegPrimesNum);
        m_threadsVc.emplace_back(m_PNSearchVc[i]);
    }

    for(uint32_t i = 0; i < m_nNumOfThreads; ++i)
    {
        m_threadsVc[i].join();
    }
}

/**
 * @brief Set specific derived class from the abstract class PrimesOutput to set the output method behaviour
 * @param pOutput Pointer to the abstract class PrimesOutput, which points to the specific derived class
 * @return None
 */
void FindPrimes::setOutput(PrimesOutput *pOutput)
{
    if(m_pOutput)
    {
        delete m_pOutput;
    }

    m_pOutput = pOutput;
}

/**
 * @brief Method to output prime numbers by the way which has been set in the implementation of the derived class from
 *        the abstract class PrimesOutput
 * @param None
 * @return None
 */
void FindPrimes::output() const
{
    m_pOutput->output(m_pPrimeNumVector);
}

//*******************************************************************************************************

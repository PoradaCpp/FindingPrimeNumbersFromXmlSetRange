/**
  ******************************************************************************
  * @file    interval.hpp
  * @author  Alexander Porada
  *          a.porada@online.ua
  * @date    23-November-2018
  * @brief   Simple structure to store numeric interval in it
  ******************************************************************************
*/

#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <stdint.h>

struct Interval
{
    uint32_t m_nLowIntervalSide;
    uint32_t m_nHighIntervalSide;

    Interval(uint32_t nLow, uint32_t nHigh): m_nLowIntervalSide(nLow), m_nHighIntervalSide(nHigh) {}
    Interval(): m_nLowIntervalSide(0), m_nHighIntervalSide(0) {}

    bool operator < (const Interval &R) const                 // For std::sort
    {
        return (m_nLowIntervalSide < R.m_nLowIntervalSide && m_nHighIntervalSide < R.m_nHighIntervalSide);
    }
};

#endif // INTERVAL_HPP

//*****************************************************************************************
